#include "uieventprocessor.h"

UiEventProcessor::UiEventProcessor(ConnectionProvider *provider, QObject *parent)
    : QObject{parent}
{
    this->connectionProvider = provider;
}

UiEventProcessor::~UiEventProcessor()
{
    connectionProvider->setActiveConnection(NONE);
    delete connectionProvider;
}

void UiEventProcessor::onSocketsConnectionClicked()
{
    qDebug() << "Sockets button clicked";
    if (connectionProvider->setActiveConnection(SOCKETS)) {
        emit socketsConnected();
    } else {
        emit connectionFailed();
    }
}

void UiEventProcessor::onPipesConnectionClicked()
{
    qDebug() << "Pipes button clicked";
    if (connectionProvider->setActiveConnection(PIPES)) {
        emit pipesConnected();
    } else {
        emit connectionFailed();
    }
}

void UiEventProcessor::onMailslotsConnectionClicked()
{
    qDebug() << "Mailslots button clicked";
    if (connectionProvider->setActiveConnection(MAILSLOTS)) {
        emit mailslotsConnected();
    } else {
        emit connectionFailed();
    }
}

void UiEventProcessor::onMessageSend(QString message)
{
    connectionProvider->sendChatMessage(message);
}

void UiEventProcessor::onLoginClicked(const QString &name, const QString &password)
{
    connectionProvider->sendLoginMessage(name, password);
}

void UiEventProcessor::onRegisterClicked(const QString &name, const QString &password)
{
    connectionProvider->sendRegisterMessage(name, password);
}
