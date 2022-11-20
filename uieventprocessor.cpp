#include "uieventprocessor.h"

UiEventProcessor::UiEventProcessor(SocketClient *client, QObject *parent)
    : QObject{parent}
{
    this->client = client;
}

void UiEventProcessor::sendSignalToAppendMessage(QString message)
{
    emit appendMessage(message);
    qDebug() << "in send signal: " << message;
}
