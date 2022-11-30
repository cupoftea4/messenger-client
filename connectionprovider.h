#ifndef CONNECTIONPROVIDER_H
#define CONNECTIONPROVIDER_H

#include "connectins/connection.h"
#include <QDebug>
#include "jsonfactory.h"

using std::map;

class ConnectionProvider
{
public:
    ConnectionProvider(map<ConnectionType, Connection *> connections);
    bool setActiveConnection(ConnectionType type);

    void sendRegisterMessage(const QString &name, const QString &password);
    void sendLoginMessage(const QString &name, const QString &password);
    void sendChatMessage(const QString &message);

private:
    bool init();
    void close();

    void handleRawMessage(const char *message);

    ConnectionType activeConnection = NONE;
    map<ConnectionType, Connection *> connections;

};

#endif // CONNECTIONPROVIDER_H
