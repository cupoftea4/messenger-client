#include "pipeconnection.h"

PipeConnection::PipeConnection(ServerEventService *serverEventService)
{
    this->serverEventService = serverEventService;
}

bool PipeConnection::init() {
    int pid = GetCurrentProcessId();
    std::wstring clientSlotName = L"\\\\.\\pipe\\messenger_client_" + std::to_wstring(pid);
    pipeName = const_cast<wchar_t *>(clientSlotName.c_str());

    HANDLE hPipe = CreateNamedPipe(
                pipeName,
                PIPE_ACCESS_INBOUND | FILE_FLAG_FIRST_PIPE_INSTANCE,
                PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_NOWAIT,
                PIPE_UNLIMITED_INSTANCES,
                0,
                0,
                0,
                NULL
                );

    if (hPipe == INVALID_HANDLE_VALUE) {
        return false;
    }
    pipe = hPipe;

    HANDLE hServer = CreateFile(SERVER_NAME,
         GENERIC_WRITE,
         FILE_SHARE_READ,
         (LPSECURITY_ATTRIBUTES) NULL,
         OPEN_EXISTING,
         FILE_ATTRIBUTE_NORMAL,
         (HANDLE) NULL);
    if(hServer == INVALID_HANDLE_VALUE) {
        CloseHandle(pipe);
        pipe = NULL;
        return false;
    }
    serverSlot = hServer;

    notifyServerJoin();
    startCheckingMessages();
    return true;
}

bool PipeConnection::isInited() {
    return pipe != NULL && serverSlot != NULL && serverPipe != NULL;
}

bool PipeConnection::isServer() {
    return false;
}

void PipeConnection::notifyServerJoin() {
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

void PipeConnection::disconnect() {
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
    CloseHandle(serverPipe);
    serverPipe = NULL;
    CloseHandle(pipe);
    pipe = NULL;
}

void PipeConnection::sendRawMessage(const char *message) {
    DWORD bytesWritten = 0;
    std::wstring prefixed = L"M:" + QString(message).toStdWString();
    LPCVOID msg = prefixed.c_str();
    WriteFile(serverPipe,
         msg,
         prefixed.size()*sizeof(wchar_t),
         &bytesWritten,
         (LPOVERLAPPED) NULL);
}

void PipeConnection::startCheckingMessages() {
    std::thread thread([this](){
        int bufSize = 1024*1024;
        while(pipe != NULL) {
            DWORD readSize = 0;
            TCHAR chBuf[bufSize];
            std::fill(chBuf, chBuf+bufSize, L'\0'); //reset buffer
            bool success = ReadFile(
                 pipe,    // pipe handle
                 chBuf,    // buffer to receive reply
                 bufSize*sizeof(TCHAR),  // size of buffer
                 &readSize,  // number of bytes read
                 NULL);

            if (success) {
                std::wstring test(chBuf);
                std::string test2(test.begin(), test.end());
                QByteArray str(test2.c_str(), test2.length());
                qDebug() << "Received information: " << str;
                QJsonParseError jsonError;
                QJsonDocument document = QJsonDocument::fromJson(str, &jsonError);
                if(jsonError.error != QJsonParseError::NoError || !document.isObject()) {
                    qDebug() << "Error json upload";
                    continue;
                }
                QJsonObject obj(document.object());
                serverEventService->handleEvent(obj);

            }

            std::this_thread::sleep_for(50ms);
        }
    });
    thread.detach();
}

void PipeConnection::addServerPipe() {
    int pid = GetCurrentProcessId();
    std::wstring slotName = L"\\\\.\\pipe\\messenger_server_" + std::to_wstring(pid);
    HANDLE hServer = CreateFile(slotName.c_str(),
                                 GENERIC_WRITE,
                                 0,
                                 (LPSECURITY_ATTRIBUTES) NULL,
                                 OPEN_EXISTING,
                                 0,
                                 (HANDLE) NULL);
    if(hServer != INVALID_HANDLE_VALUE) {
        serverPipe = hServer;
    }
}

void PipeConnection::setMessageReceiver(std::function<void(std::wstring)> lambda) {
    messageHandler = lambda;
}
