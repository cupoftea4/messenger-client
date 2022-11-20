#include "signalsconnector.h"
#include "qqmlengine.h"

SignalsConnector::SignalsConnector(QObject *parent)
    : QObject{parent}
{

}

bool SignalsConnector::connectAuthentication(QQuickView& view, std::map<std::string, ActionHandler*> handlers, UiEventProcessor *uiProcessor)
{
    // get root & ui elements to connect to
    QObject *root = view.rootObject();
    QObject *button = root->findChild<QObject*>("login_btn");

    if (button == nullptr)
        return false;

    // get action handlers
    ActionHandler *registerHandler = handlers[ACTION_REGISTER];

    // register action handlers
    view.engine()->rootContext()->setContextProperty("RegisterHandler", registerHandler);

    // connects
    QObject::connect(button, SIGNAL(qmlSignal(QString,QString)),
                        uiProcessor, SLOT(cppSlot(QString,QString)));
    QObject::connect(registerHandler, SIGNAL(failedRegistration()),
                        root, SLOT(onFailedRegistration()), Qt::QueuedConnection);
    return true;
}

bool SignalsConnector::connectSignals(QQuickView& view, std::map<std::string, ActionHandler*> handlers, UiEventProcessor *uiProcessor)
{
    view.engine()->rootContext()->setContextProperty("UiProcessor", uiProcessor);
    QObject::connect(uiProcessor, SIGNAL(appendMessage(QString)),
                        view.rootObject(), SLOT(onAppendMessage(QString)), Qt::QueuedConnection);
    return connectAuthentication(view, handlers, uiProcessor);
}
