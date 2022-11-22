#ifndef PIPECLIENT_H
#define PIPECLIENT_H

#include <windows.h>
#include "communication.h"
#include <thread>
#include <chrono>
#include <QDebug>

using namespace std::chrono_literals;


class PipeClient : public Communication
{
public:

    constexpr static LPCWSTR SERVER_NAME = TEXT("\\\\.\\mailslot\\messenger_server_notify");

    PipeClient();
    bool init() override;
    bool isInited() override;
    bool isServer() override;
    void sendMessage(std::wstring) ;
    void setMessageReceiver(std::function<void(std::wstring)>) override;
    void disconnect() override;

private:
    void startCheckingMessages();
    void notifyServerJoin();
    void addServerPipe();

    LPCWSTR pipeName;
    HANDLE pipe;
    HANDLE serverPipe;
    HANDLE serverSlot;
    std::function<void(std::wstring)> messageHandler;
};

#endif // PIPECLIENT_H
