#include "uieventprocessor.h"

UiEventProcessor::UiEventProcessor(SocketConnection *client, QObject *parent)
    : QObject{parent}
{
    this->connection = client;
}

void UiEventProcessor::connectionFailed()
{
    emit showConnectionFailed();
}


void UiEventProcessor::onMessageSend(QString message)
{
    qDebug() << "Trying to send message:" << message;
    char * rawMsg = JsonFactory::sendMsgJson(message).c_str();
    connection->sendRawMessage(rawMsg);
    delete [] rawMsg;
}

void UiEventProcessor::onLoginClicked(const QString &name, const QString &password)
{
    qDebug() << "Trying to login in with name:" << name << "and pwd: " << password;
    char * rawMsg = JsonFactory::loginJson(name, password).c_str();
    connection->sendRawMessage(rawMsg);
    delete [] rawMsg;
}

void UiEventProcessor::onRegisterClicked(const QString &name, const QString &password)
{
    qDebug() << "Trying to register in with name:" << name << "and pwd: " << password;
    char * rawMsg = JsonFactory::registerJson(name, password).c_str();
    connection->sendRawMessage(rawMsg);
    delete [] rawMsg;
}
