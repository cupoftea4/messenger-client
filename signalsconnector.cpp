#include "signalsconnector.h"
#include "qqmlengine.h"

SignalsConnector::SignalsConnector(QObject *parent)
    : QObject{parent}
{

}

bool SignalsConnector::connectRegisterHandler(QQuickView& view, ActionHandler* handler, UiEventProcessor *uiProcessor)
{
    // get root & ui elements to connect to
    QObject *root = view.rootObject();
    QObject *button = root->findChild<QObject*>("register_btn");

    if (button == nullptr)
        return false;

    // register action handlers
    view.engine()->rootContext()->setContextProperty("RegisterHandler", handler);

    // connects
    QObject::connect(button, SIGNAL(registerClicked(QString,QString)),
                        uiProcessor, SLOT(onRegisterClicked(QString,QString)));
    QObject::connect(handler, SIGNAL(failedRegistration()),
                        root, SLOT(onFailedRegistration()), Qt::QueuedConnection);
    QObject::connect(handler, SIGNAL(successfulRegistration(QString)),
                        root, SLOT(onSuccessfulRegistration(QString)), Qt::QueuedConnection);
    return true;
}

bool SignalsConnector::connectMessageHandler(QQuickView &view, ActionHandler *msgHandler, UiEventProcessor *uiProcessor)
{
    // get root & ui elements to connect to
    QObject *root = view.rootObject();
    QObject *button = root->findChild<QObject*>("send_btn");

    if (button == nullptr)
        return false;


    view.engine()->rootContext()->setContextProperty("MessageHandler", msgHandler);

    // connects
    QObject::connect(button, SIGNAL(sendMessage(QString)),
                        uiProcessor, SLOT(onMessageSend(QString)));
    QObject::connect(msgHandler, SIGNAL(messageReceived(QString,QString)),
                        root, SLOT(onMessageReceived(QString,QString)), Qt::QueuedConnection);
    return true;
}

bool SignalsConnector::connectLoginHandler(QQuickView &view, ActionHandler *handler, UiEventProcessor *uiProcessor)
{
    // get root & ui elements to connect to
    QObject *root = view.rootObject();
    QObject *button = root->findChild<QObject*>("login_btn");

    if (button == nullptr)
        return false;


    // register action handlers
    view.engine()->rootContext()->setContextProperty("LoginHandler", handler);

    // connects
    QObject::connect(button, SIGNAL(loginClicked(QString,QString)),
                        uiProcessor, SLOT(onLoginClicked(QString,QString)));
    QObject::connect(handler, SIGNAL(failedLogin()),
                        root, SLOT(onFailedLogin()), Qt::QueuedConnection);
    QObject::connect(handler, SIGNAL(successfulLogin(QString)),
                        root, SLOT(onSuccessfulLogin(QString)), Qt::QueuedConnection);
    return true;
}

bool SignalsConnector::connectSignals(QQuickView& view, std::map<QString, ActionHandler*> handlers, UiEventProcessor *uiProcessor)
{
    // TODO: refactor this

    if (handlers.find(ACTION_MESSAGE) != handlers.end()) {
        connectMessageHandler(view, handlers[ACTION_MESSAGE], uiProcessor);
    }
    if (handlers.find(ACTION_LOGIN) != handlers.end()) {
        connectLoginHandler(view, handlers[ACTION_LOGIN], uiProcessor);
    }
    if (handlers.find(ACTION_REGISTER) != handlers.end()) {
        connectRegisterHandler(view, handlers[ACTION_REGISTER], uiProcessor);
    }
    return true;
}


