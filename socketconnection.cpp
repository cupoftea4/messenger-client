#include "socketconnection.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <iostream>
#include <QIODevice>
/*
 * actions:
 * SEND-send message(text)
 * JOIN-connect client to server
 *
*/


std::vector<std::string> split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

SocketConnection::SocketConnection(ServerEventService *serverEventService) {
    this->serverEventService = serverEventService;
}

bool SocketConnection::init() {
    WSADATA wsaData;

    int iResult;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        qDebug() << "WSAStartup failed:" << iResult << "\n";
        return false;
    }
    struct addrinfo *result = NULL, *ptr = NULL, hints;

    ZeroMemory(&hints, sizeof (hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    if(ip.size() == 0) ip = "localhost";

    iResult = getaddrinfo(ip.c_str(), this->port.c_str(), &hints, &result);
    if (iResult != 0) {
        qDebug() << "getaddrinfo failed with code" << iResult << "\n";
        WSACleanup();
        return false;
    }

    for (ptr = result; ptr != nullptr; ptr = ptr->ai_next){
        sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (sock == INVALID_SOCKET) {
            WSACleanup();
            qDebug() << "socket() failed\n";
            return false;
        }
        iResult = connect(sock, ptr->ai_addr, static_cast<int>(ptr->ai_addrlen));
        if (iResult == SOCKET_ERROR) {
            qDebug() << "Socket error:" << WSAGetLastError() << "\n";
            closesocket(sock);
            sock = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if(sock == INVALID_SOCKET) {
        qDebug() << "Failed to connect to socket!\n";
        WSACleanup();
        return false;
    }
    u_long mode = 1;
    ioctlsocket(sock, FIONBIO, &mode); //non-blocking mode

    notifyServerJoin();
    startCheckingMessages();

    return true;
}

bool SocketConnection::isInited() {
    return sock != INVALID_SOCKET;
}

bool SocketConnection::isServer() {
    return false;
}

void SocketConnection::disconnect() {
    qDebug() << "Disconneting sockets";
    int pid = GetCurrentProcessId();
    std::string s = "L:";
    s+=std::to_string(pid);
    sendRawMessage((char*)s.c_str());
    std::this_thread::sleep_for(50ms); // non-blocking socket just gets killed even if it tried to send message
    closesocket(sock);
    sock = INVALID_SOCKET;
    WSACleanup();
}

void SocketConnection::startCheckingMessages() {
    std::thread thread([this] {
        int bufSize = 1024*1024;
        int iResult = 0;
        while(isInited()) {
            char *chBuf=new char[bufSize];
            std::fill(chBuf, chBuf+bufSize, L'\0');
            iResult = recv(sock, chBuf, bufSize, 0);
            if(iResult > 0) {
                qDebug() << "Received information: " << chBuf;
                QJsonParseError jsonError;
                QJsonDocument document = QJsonDocument::fromJson(chBuf, &jsonError);
                if(jsonError.error != QJsonParseError::NoError){
                    qDebug() << "Error json upload";
                    continue;
                }
                if(!document.isObject())
                {
                    continue;
                }
                QJsonObject obj(document.object());
                serverEventService->handleEvent(obj);

            } else if (iResult == 0) {
                qDebug() << "Something went wrong. Connection lost";
                serverEventService->handleDisconnect();
                disconnect();
            }
            std::this_thread::sleep_for(50ms);
            delete[] chBuf;
        }
    });
    thread.detach();
}

void SocketConnection::sendRawMessage(const char* chBuf) {
    qDebug() << "Sending raw message: " << chBuf;
    send(sock, chBuf, strlen(chBuf), 0 );
}


void SocketConnection::notifyServerJoin() {
    int pid = GetCurrentProcessId();
    sendRawMessage(JsonFactory::sendMsgJson(QString::number(pid)).c_str());
}

void SocketConnection::setMessageReceiver(std::function<void(std::wstring)> lambda) {
    renderMessage = lambda;
}
