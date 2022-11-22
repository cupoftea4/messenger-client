#ifndef MAILSLOTCLIENT_H
#define MAILSLOTCLIENT_H

#include "communication.h"

#include <string>
#include <vector>
#include <functional>
#include <thread>
#include <chrono>
#include <windows.h>

using namespace std::chrono_literals;

class MailslotClient : public Communication
{
public:
    constexpr static LPCWSTR SERVER_NAME = TEXT("\\\\.\\mailslot\\messenger_server");

    MailslotClient();
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

#endif // MAILSLOTCLIENT_H
