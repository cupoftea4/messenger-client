#ifndef MESSENGERCONFIGURATION_H
#define MESSENGERCONFIGURATION_H

#include "signalsconnector.h"
#include "action_handles/messageactionhandler.h"
#include "action_handles/loginactionhandler.h"
#include "action_handles/registeractionhandler.h"
#include "connectins/socketconnection.h"
#include "connectins/mailslotconnection.h"
#include "connectins/pipeconnection.h"
#include "quickviewwrapper.h"

#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include <QQuickStyle>

const std::string SERVER_ADDR = "localhost";

class MessengerConfiguration
{
public:
    MessengerConfiguration();
    bool init();

private:
    map<QString, ActionHandler *>  getHandlers();
    ServerEventService *getServerEventService();
    map<ConnectionType, Connection *> getConnections();
    ConnectionProvider *getConnectionProvider();
    UiEventProcessor *getUiEventProcessor();
    QQuickView *getQuickView();
    SignalsConnector *getSignalsConnector();

    map<QString, ActionHandler *> handlers;
    ServerEventService *serverEventService = nullptr;
    map<ConnectionType, Connection *> connections;
    ConnectionProvider *connectionProvider = nullptr;
    UiEventProcessor *uiEventProcessor = nullptr;
    QQuickView *quickView = nullptr;
    SignalsConnector *signalsConnector = nullptr;

};

#endif // MESSENGERCONFIGURATION_H
