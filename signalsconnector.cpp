#include "signalsconnector.h"
#include "qqmlengine.h"

SignalsConnector::SignalsConnector(QObject *parent)
    : QObject{parent}
{
}

bool SignalsConnector::connect(QQuickView *view, ServerEventService *eventService, UiEventProcessor *uiProcessor)
{
    connectUiProcessor(view, uiProcessor);
    connectServerEventService(view, eventService);

    map<QString, ActionHandler *> handlers = eventService->getHandlers();
    if (handlers.find(ACTION_MESSAGE) != handlers.end()) {
        connectMessageHandler(view, handlers[ACTION_MESSAGE]);
    }
    if (handlers.find(ACTION_LOGIN) != handlers.end()) {
        connectLoginHandler(view, handlers[ACTION_LOGIN]);
    }
    if (handlers.find(ACTION_REGISTER) != handlers.end()) {
        connectRegisterHandler(view, handlers[ACTION_REGISTER]);
    }
    return true;
}

void SignalsConnector::connectUiProcessor(QQuickView *view, UiEventProcessor *uiProcessor)
{
    QObject *root = view->rootObject();


    // ui slots connects
    view->engine()->rootContext()->setContextProperty("UiProcessor", uiProcessor);
    QObject::connect(uiProcessor, SIGNAL(socketsConnected()),
                        root, SLOT(onSocketsConnected()), Qt::QueuedConnection);
    QObject::connect(uiProcessor, SIGNAL(pipesConnected()),
                        root, SLOT(onPipesConnected()), Qt::QueuedConnection);
    QObject::connect(uiProcessor, SIGNAL(mailslotsConnected()),
                        root, SLOT(onMailslotsConnected()), Qt::QueuedConnection);

    // ui signals connects
    connectConnctionTypeButtons(root, uiProcessor);
    connectActionButtons(root, uiProcessor);

}

void SignalsConnector::connectServerEventService(QQuickView *view, ServerEventService *eventService)
{
    QObject *root = view->rootObject();

    // add server event service as ui target
    view->engine()->rootContext()->setContextProperty("ServerEventService", eventService);

    // ui slots connects
    QObject::connect(eventService, SIGNAL(showServerDisconnected()),
                        root, SLOT(onShowServerDisconnected()), Qt::QueuedConnection);
}

bool SignalsConnector::connectRegisterHandler(QQuickView *view, ActionHandler* handler)
{
    QObject *root = view->rootObject();

    // add register action handler as ui target
    view->engine()->rootContext()->setContextProperty("RegisterHandler", handler);

    // ui slots connects
    QObject::connect(handler, SIGNAL(failedRegistration()),
                        root, SLOT(onFailedRegistration()), Qt::QueuedConnection);
    QObject::connect(handler, SIGNAL(successfulRegistration(QString)),
                        root, SLOT(onSuccessfulRegistration(QString)), Qt::QueuedConnection);
    return true;
}

bool SignalsConnector::connectMessageHandler(QQuickView *view, ActionHandler *msgHandler)
{
    QObject *root = view->rootObject();

    // add message action handler as ui target
    view->engine()->rootContext()->setContextProperty("MessageHandler", msgHandler);

    // ui slots connects
    QObject::connect(msgHandler, SIGNAL(messageReceived(QString,QString)),
                        root, SLOT(onMessageReceived(QString,QString)), Qt::QueuedConnection);
    return true;
}

bool SignalsConnector::connectLoginHandler(QQuickView *view, ActionHandler *handler)
{
    QObject *root = view->rootObject();

    // add login action handler as ui target
    view->engine()->rootContext()->setContextProperty("LoginHandler", handler);

    // ui slots connects
    QObject::connect(handler, SIGNAL(failedLogin()),
                        root, SLOT(onFailedLogin()), Qt::QueuedConnection);
    QObject::connect(handler, SIGNAL(successfulLogin(QString)),
                        root, SLOT(onSuccessfulLogin(QString)), Qt::QueuedConnection);
    return true;
}

void SignalsConnector::connectActionButtons(QObject *root, UiEventProcessor *uiProcessor)
{
    QObject *sendButton = root->findChild<QObject*>("send_btn");
    QObject *loginButton = root->findChild<QObject*>("login_btn");
    QObject *registerButton = root->findChild<QObject*>("register_btn");

    if (sendButton == nullptr || loginButton == nullptr || registerButton == nullptr)
        return;

    QObject::connect(sendButton, SIGNAL(sendMessage(QString)),
                        uiProcessor, SLOT(onMessageSend(QString)));
    QObject::connect(loginButton, SIGNAL(loginClicked(QString,QString)),
                        uiProcessor, SLOT(onLoginClicked(QString,QString)));
    QObject::connect(registerButton, SIGNAL(registerClicked(QString,QString)),
                        uiProcessor, SLOT(onRegisterClicked(QString,QString)));

}

void SignalsConnector::connectConnctionTypeButtons(QObject *root, UiEventProcessor *uiProcessor)
{
    QObject *socketsButton = root->findChild<QObject*>("sockets_btn");
    QObject *pipesButton = root->findChild<QObject*>("pipes_btn");
    QObject *mailslotsButton = root->findChild<QObject*>("mailslots_btn");

    if (socketsButton == nullptr || pipesButton == nullptr || mailslotsButton == nullptr)
        return;

    QObject::connect(socketsButton, SIGNAL(socketsClicked()),
                        uiProcessor, SLOT(onSocketsConnectionClicked()));
    QObject::connect(pipesButton, SIGNAL(pipesClicked()),
                        uiProcessor, SLOT(onPipesConnectionClicked()));
    QObject::connect(mailslotsButton, SIGNAL(mailslotsClicked()),
                        uiProcessor, SLOT(onMailslotsConnectionClicked()));
}
