#ifndef SOCKETCONNECTION_H
#define SOCKETCONNECTION_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <algorithm>
#include <thread>
#include <chrono>
#include <QDebug>
#include <vector>
#include <iostream>
#include "connection.h"
#include "jsonfactory.h"

using namespace std::chrono_literals;
const char* const DEFAULT_PORT = "12321";

class SocketConnection : public Connection
{
public:
    SocketConnection(ServerEventService *serverEventService);
    bool init() override;
    bool isInited() override;
    bool isServer() override;
    void setMessageReceiver(std::function<void(std::wstring)>) override;
    void disconnect() override;

    void sendRawMessage(const char*) override;

private:
    void startCheckingMessages();
    void notifyServerJoin();

    SOCKET sock;
    std::function<void(std::wstring)> renderMessage;
    std::string ip = "localhost";
    std::string port = DEFAULT_PORT;

};


#endif // SOCKETCONNECTION_H
