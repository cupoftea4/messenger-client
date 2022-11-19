#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

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

class SocketClient : public Communication
{
public:
    SocketClient(std::string ip, std::map<std::string, ActionHandler*> &handles);
    ~SocketClient();
    bool init() override;
    bool isInited() override;
    bool isServer() override;
    void sendMessage(std::wstring) override;
    void setMessageReceiver(std::function<void(std::wstring)>) override;
    void disconnect() override;
    char* messageToJSON(std::string type,std::wstring str);

    const char* DEFAULT_PORT = "12321";

private:
    void startCheckingMessages();
    void notifyServerJoin();
    void sendRawMessage(char*);

    SOCKET sock;
    std::function<void(std::wstring)> messageHandler;
    std::string ip = "localhost";
    std::string port = DEFAULT_PORT;
    std::map<std::string, ActionHandler*> actionHandles;
};

#endif // SOCKETCLIENT_H
