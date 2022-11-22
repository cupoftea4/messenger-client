#ifndef MESSENGERCONFIGURATION_H
#define MESSENGERCONFIGURATION_H

#include "signalsconnector.h"
#include "messageactionhandler.h"
#include "loginactionhandler.h"
#include "registeractionhandler.h"
#include "socketconnection.h"
#include "mailslotconnection.h"
#include "pipeconnection.h"
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
    map<QString, ActionHandler *>  *getHandlers(); // if empty, create and put `ActionHandler *`s into map
    ServerEventService *getServerEventService(); // if nullptr, create. Call getHandlers(). Return
    map<ConnectionType, Connection *> getConnections(); // if empty, create and put Connection *`s into map
    ConnectionProvider *getConnectionProvider(); // if nullptr, create. Return
    UiEventProcessor *getUiEventProcessor(); // if nullptr, create. Return
    QQuickView *getQuickView(); // if nullptr, create. Return
    SignalsConnector *getSignalsConnector(); // if nullptr, create. Return

    map<QString, ActionHandler *> * handlers = nullptr;
    ServerEventService *serverEventService = nullptr;
    map<ConnectionType, Connection *> connections = map<ConnectionType, Connection *>();
    ConnectionProvider *connectionProvider = nullptr;
    UiEventProcessor *uiEventProcessor = nullptr;
    QQuickView *quickView = nullptr;
    SignalsConnector *signalsConnector = nullptr;

};

#endif // MESSENGERCONFIGURATION_H
