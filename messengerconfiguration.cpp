#include "messengerconfiguration.h"

MessengerConfiguration::MessengerConfiguration() {}

bool MessengerConfiguration::init()
{
    return getSignalsConnector() != nullptr;
}

map<QString, ActionHandler *> *MessengerConfiguration::getHandlers()
{
//    qDebug() << "Map is empty?: " << handlers.empty();
    if (handlers != nullptr) {
        return handlers;
    }
    handlers = new map<QString, ActionHandler *>;
    ActionHandler *msgHandler = new MessageActionHandler;
    ActionHandler *loginHandler = new LoginActionHandler;
    ActionHandler *registerHandler = new RegisterActionHandler;

    (*handlers)[ACTION_MESSAGE] = msgHandler;
    (*handlers)[ACTION_LOGIN] = loginHandler;
    (*handlers)[ACTION_REGISTER] = registerHandler;
    qDebug() << "Map size in config: " << handlers->size();

    return handlers;
}

ServerEventService *MessengerConfiguration::getServerEventService()
{
    if (serverEventService != nullptr)
        return serverEventService;

    return serverEventService = new ServerEventService(getHandlers());
}

map<ConnectionType, Connection *> MessengerConfiguration::getConnections()
{
    if (!connections.empty())
        return connections;

    Connection *socketConnection = new SocketConnection(serverEventService);
    Connection *pipeConnection = new PipeConnection(serverEventService);
    Connection *mailslotConnection = new MailslotConnection(serverEventService);

    connections[SOCKETS] = socketConnection;
    connections[PIPES] = pipeConnection;
    connections[MAILSLOTS] = mailslotConnection;

    return connections;
}

ConnectionProvider *MessengerConfiguration::getConnectionProvider()
{
    if (connectionProvider != nullptr)
        return connectionProvider;
    return connectionProvider = new ConnectionProvider(getConnections());
}

UiEventProcessor *MessengerConfiguration::getUiEventProcessor()
{
    if (uiEventProcessor != nullptr)
        return uiEventProcessor;
    return uiEventProcessor = new UiEventProcessor(getConnectionProvider());
}

QQuickView *MessengerConfiguration::getQuickView()
{
    if (quickView != nullptr)
        return quickView;

    quickView = new QuickViewWrapper(getUiEventProcessor());
    quickView->engine()->addImportPath("qrc:/qml/imports");
    QQuickStyle::setStyle("Material");
    quickView->setSource(QUrl("qrc:/qml/content/Screen01.ui.qml"));
    if (!quickView->errors().isEmpty()) {
        return nullptr;
    }
    quickView->show();
    return quickView;
}

SignalsConnector *MessengerConfiguration::getSignalsConnector()
{
    QQuickView * view = getQuickView();
    if (view == nullptr)
        return nullptr;
    if (signalsConnector != nullptr)
        return signalsConnector;

    signalsConnector = new SignalsConnector();
    signalsConnector->connect(view, getServerEventService(), getUiEventProcessor());
    return signalsConnector;
}
