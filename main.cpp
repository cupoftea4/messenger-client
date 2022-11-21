#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include <QQuickStyle>
#include "signalsconnector.h"
#include "socketconnection.h"
#include "registeractionhandler.h"
#include "actionhandler.h"
#include "messageactionhandler.h"
#include "jsonfactory.h"
#include "uieventprocessor.h"
#include "loginactionhandler.h"


std::map<QString, ActionHandler*> createHandlesMap();

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    SignalsConnector uiConnector;
    std::map<QString, ActionHandler*> jsonHandlers = createHandlesMap();
    SocketConnection *connection = new SocketConnection("localhost", jsonHandlers);
    UiEventProcessor *uiProcessor = new UiEventProcessor(connection);


    QQuickView view;
    view.engine()->addImportPath("qrc:/qml/imports");
    QQuickStyle::setStyle("Material");
    view.setSource(QUrl("qrc:/qml/content/Screen01.ui.qml"));
    if (!view.errors().isEmpty()) {
        delete connection;
        delete uiProcessor;
        return -1;
    }
    view.show();

    uiConnector.connectSignals(view, jsonHandlers, uiProcessor);

    if (!connection->init()) {
        qDebug() <<  "Couldn't init connection";
//        uiProcessor->connectionFailed();
    }

    return app.exec();
}


std::map<QString, ActionHandler*> createHandlesMap() {
    std::map<QString, ActionHandler*> jsonHandlers;

    ActionHandler *registerHandler = new RegisterActionHandler;
    ActionHandler *messageHandler = new MessageActionHandler;
    ActionHandler *loginHandler = new LoginActionHandler;

    jsonHandlers[ACTION_REGISTER] = registerHandler;
    jsonHandlers[ACTION_MESSAGE] = messageHandler;
    jsonHandlers[ACTION_LOGIN] = loginHandler;

    return jsonHandlers;
}
