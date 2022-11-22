#include "connectionprovider.h"

ConnectionProvider::ConnectionProvider(map<ConnectionType, Connection *> connections)
{
    this->connections = connections;
}

bool ConnectionProvider::setActiveConnection(ConnectionType type)
{
    close();
    activeConnection = type;
    return init();
}

void ConnectionProvider::sendRegisterMessage(const QString &name, const QString &password)
{
    if (activeConnection == NONE)
        return;
    qDebug() << "Trying to register in with name:" << name << "and pwd: " << password;
    handleRawMessage(JsonFactory::registerJson(name, password).c_str());
}

void ConnectionProvider::sendLoginMessage(const QString &name, const QString &password)
{
    if (activeConnection == NONE)
        return;
    qDebug() << "Trying to login in with name:" << name << "and pwd: " << password;
    handleRawMessage(JsonFactory::loginJson(name, password).c_str());
}

void ConnectionProvider::sendChatMessage(const QString &message)
{
    if (activeConnection == NONE)
        return;
    qDebug() << "Trying to send message:" << message;
    handleRawMessage(JsonFactory::sendMsgJson(message).c_str());
}

void ConnectionProvider::handleRawMessage(const char *message)
{
    connections[activeConnection]->sendRawMessage(message);
    delete [] message;
}

void ConnectionProvider::close()
{
    if (activeConnection == NONE)
        return;

    connections[activeConnection]->disconnect();
}

bool ConnectionProvider::init()
{
    if (activeConnection == NONE)
        return false;

    return connections[activeConnection]->init();
}
