#ifndef CONNECTION_H
#define CONNECTION_H

#include <functional>
#include <string>
#include <QObject>
#include "servereventservice.h"

enum ConnectionType {NONE, SOCKETS, MAILSLOTS};

class Connection {

public:
    virtual ~Connection() {
        // TODO: ...
        qDebug() << "Connection destructor called";
        if (serverEventService != nullptr)
            delete serverEventService;
    }
    virtual bool init() = 0;
    virtual bool isInited() = 0;
    virtual bool isServer() = 0;
    virtual void sendRawMessage(const char *) = 0;
    virtual void setMessageReceiver(std::function<void(std::wstring)>) = 0;
    virtual void disconnect() = 0;
protected:
    ServerEventService *serverEventService = nullptr;

};

#endif // CONNECTION_H
