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
#include "communication.h"
#include "jsonfactory.h"
#include "registeractionhandler.h"

using namespace std::chrono_literals;

class SocketConnection : public Communication
{
public:
    SocketConnection(std::string ip, std::map<QString, ActionHandler*> &handles);
    bool init() override;
    bool isInited() override;
    bool isServer() override;
    void setMessageReceiver(std::function<void(std::wstring)>) override;
    void disconnect() override;

    void sendRawMessage(const char*) override;
    const char* DEFAULT_PORT = "12321";

private:
    void startCheckingMessages();
    void notifyServerJoin();

    SOCKET sock;
    std::function<void(std::wstring)> renderMessage;
    std::string ip = "localhost";
    std::string port = DEFAULT_PORT;
    std::map<QString, ActionHandler*> actionHandles;
};


#endif // SOCKETCONNECTION_H
