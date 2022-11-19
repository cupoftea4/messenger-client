#include "uieventprocessor.h"

UiEventProcessor::UiEventProcessor(SocketClient *client, QObject *parent)
    : QObject{parent}
{
    this->client = client;
}
