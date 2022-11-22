#include "mailslotconnection.h"

MailslotConnection::MailslotConnection(ServerEventService *serverEventService) {
   this->serverEventService = serverEventService;
}

bool MailslotConnection::init() {
    int pid = GetCurrentProcessId();
    std::wstring clientSlotName = L"\\\\.\\mailslot\\messenger_client_";
    clientSlotName += std::to_wstring(pid);
    slotName = const_cast<wchar_t *>(clientSlotName.c_str());

    HANDLE hSlot = CreateMailslot(slotName,
            0,                             // no maximum message size
            MAILSLOT_WAIT_FOREVER,         // no time-out for operations
            (LPSECURITY_ATTRIBUTES) NULL); // default security

    if (hSlot == INVALID_HANDLE_VALUE) {
        return false;
    }
    slot = hSlot;

    HANDLE hServer = CreateFile(SERVER_NAME,
         GENERIC_WRITE,
         FILE_SHARE_READ,
         (LPSECURITY_ATTRIBUTES) NULL,
         OPEN_EXISTING,
         FILE_ATTRIBUTE_NORMAL,
         (HANDLE) NULL);
    if(hServer == INVALID_HANDLE_VALUE) {
        CloseHandle(slot);
        slot = NULL;
        return false;
    }
    serverSlot = hServer;

    notifyServerJoin();
    startCheckingMessages();
    return true;
}

bool MailslotConnection::isInited() {
    return slot != NULL && serverSlot != NULL;
}

bool MailslotConnection::isServer() {
    return false;
}

void MailslotConnection::notifyServerJoin() {
    int pid = GetCurrentProcessId();
    DWORD bytesWritten = 0;
    std::wstring message = L"J:"+std::to_wstring(pid);
    LPCVOID msg = message.c_str();
    WriteFile(serverSlot,
         msg,
         message.size()*sizeof(wchar_t),
         &bytesWritten,
         (LPOVERLAPPED) NULL);
}

void MailslotConnection::disconnect() {
    if(!isInited()) return;
    int pid = GetCurrentProcessId();
    DWORD bytesWritten = 0;
    std::wstring message = L"L:"+std::to_wstring(pid);
    LPCVOID msg = message.c_str();
    WriteFile(serverSlot,
         msg,
         message.size()*sizeof(wchar_t),
         &bytesWritten,
         (LPOVERLAPPED) NULL);
    CloseHandle(serverSlot);
    serverSlot = NULL;
    CloseHandle(slot);
    slot = NULL;
}

void MailslotConnection::sendRawMessage(const char * message) {
    DWORD bytesWritten = 0;
    std::wstring prefixed = L"M:" + QString(message).toStdWString();
    LPCVOID msg = prefixed.c_str();
    WriteFile(serverSlot,
         msg,
         prefixed.size()*sizeof(wchar_t),
         &bytesWritten,
         (LPOVERLAPPED) NULL);
}

void MailslotConnection::startCheckingMessages() {
    std::thread thread([this](){
        DWORD nextSize = 0, messagesLeft = 0;
        while(slot != NULL) {
            GetMailslotInfo(slot,  // mailslot handle
                        (LPDWORD) NULL,               // no maximum message size
                        &nextSize,                   // size of next message
                        &messagesLeft,                    // number of messages
                        (LPDWORD) NULL);
            if(messagesLeft > 0) {
                DWORD readSize = 0;
                TCHAR chBuf[nextSize];
                std::fill(chBuf, chBuf+nextSize, L'\0'); //reset buffer
                bool success = ReadFile(
                     slot,    // pipe handle
                     chBuf,    // buffer to receive reply
                     nextSize*sizeof(TCHAR),  // size of buffer
                     &readSize,  // number of bytes read
                     NULL);

                if(success) {
                    char *str;
                    wcstombs(str, chBuf, wcslen(chBuf) + 1);
                    qDebug() << "Received information: " << str;
                    QJsonParseError jsonError;
                    QJsonDocument document = QJsonDocument::fromJson(str, &jsonError);
                    if(jsonError.error != QJsonParseError::NoError){
                        qDebug() << "Error json upload";
                        continue;
                    }
                    std::string type;
                    if(!document.isObject())
                    {
                        continue;
                    }
                    QJsonObject obj(document.object());
                    serverEventService->handleEvent(obj);
                }
            }

            std::this_thread::sleep_for(50ms);
        }
    });
    thread.detach();
}

void MailslotConnection::setMessageReceiver(std::function<void(std::wstring)> lambda) {
    messageHandler = lambda;
}
