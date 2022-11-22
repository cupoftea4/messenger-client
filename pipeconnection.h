#ifndef PIPECONNECTION_H
#define PIPECONNECTION_H

#include <windows.h>
#include "connection.h"
#include <thread>
#include <chrono>
#include <QDebug>
#include <QJsonDocument>
#include "servereventservice.h"

using namespace std::chrono_literals;


class PipeConnection : public Connection
{
public:

    constexpr static LPCWSTR SERVER_NAME = TEXT("\\\\.\\mailslot\\messenger_server_notify");

    PipeConnection(ServerEventService *serverEventService);
    bool init() override;
    bool isInited() override;
    bool isServer() override;
    void sendRawMessage(const char *) override;
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

#endif // PIPECONNECTION_H
