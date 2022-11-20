#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include <QQuickStyle>
#include "signalsconnector.h"
#include "socketclient.h"
#include "registeractionhandler.h"
#include "actionhandler.h"
#include "messageactionhandler.h"
#include "jsonfactory.h"
#include "uieventprocessor.h"
#include "loginactionhandler.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    SignalsConnector uiConnector;

    // create handlers
    ActionHandler *registerHandler = new RegisterActionHandler;
    ActionHandler *messageHandler = new MessageActionHandler;
    ActionHandler *loginHandler = new LoginActionHandler;
    std::map<QString, ActionHandler*> jsonHandlers;
    jsonHandlers[ACTION_REGISTER] = registerHandler;
    jsonHandlers[ACTION_MESSAGE] = messageHandler;
    jsonHandlers[ACTION_LOGIN] = loginHandler;


    QQuickView view;
    view.engine()->addImportPath("qrc:/qml/imports");
    QQuickStyle::setStyle("Material");
    view.setSource(QUrl("qrc:/qml/content/Screen01.ui.qml"));
    if (!view.errors().isEmpty()) {
        return -1;
    }
    view.show();

    SocketClient *connection = new SocketClient("localhost", jsonHandlers);
    UiEventProcessor *uiProcessor = new UiEventProcessor(connection);
    connection->init();

    uiConnector.connectSignals(view, jsonHandlers, uiProcessor);

    return app.exec();
}
