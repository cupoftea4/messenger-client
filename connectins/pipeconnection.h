#ifndef PIPECONNECTION_H
#define PIPECONNECTION_H

#include <windows.h>
#include "connection.h"
#include <thread>
#include <chrono>
#include <QDebug>
#include <QJsonDocument>
#include "servereventservice.h"
#include "jsonfactory.h"

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
    void disconnect() override;

private:
    void startCheckingMessages();
    void notifyServerJoin();
    void addServerPipe();

    LPCWSTR pipeName;
    HANDLE pipe;
    HANDLE serverPipe;
    HANDLE serverSlot;

};

#endif // PIPECONNECTION_H
