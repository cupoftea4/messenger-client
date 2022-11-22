#ifndef MAILSLOTCONNECTION_H
#define MAILSLOTCONNECTION_H

#include "connection.h"

#include <string>
#include <vector>
#include <functional>
#include <thread>
#include <chrono>
#include <windows.h>
#include <QJsonDocument>
#include "servereventservice.h"

using namespace std::chrono_literals;

class MailslotConnection : public Connection
{
public:
    constexpr static LPCWSTR SERVER_NAME = TEXT("\\\\.\\mailslot\\messenger_server");

    MailslotConnection(ServerEventService *serverEventService);
    bool init() override;
    bool isInited() override;
    bool isServer() override;
    void sendRawMessage(const char *) override;
    void setMessageReceiver(std::function<void(std::wstring)>) override;
    void disconnect() override;

private:
    void startCheckingMessages();
    void notifyServerJoin();

    LPCWSTR slotName;
    HANDLE slot;
    HANDLE serverSlot;
    std::function<void(std::wstring)> messageHandler;
};

#endif // MAILSLOTCONNECTION_H
