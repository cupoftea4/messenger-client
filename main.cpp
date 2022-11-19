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

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    SignalsConnector tester;

    // create handlers
    ActionHandler *handler = new RegisterActionHandler;
    std::map<std::string, ActionHandler*> jsonHandlers;
    jsonHandlers[ACTION_REGISTER] = handler;

    SocketClient *client = new SocketClient("localhost", jsonHandlers);
    UiEventProcessor *uiProcessor = new UiEventProcessor(client);


    QQuickView view;
    view.engine()->addImportPath("qrc:/qml/imports");
    QQuickStyle::setStyle("Material");
    view.setSource(QUrl("qrc:/qml/content/Screen01.ui.qml"));
    if (!view.errors().isEmpty())
        return -1;
    view.show();
    tester.connectSignals(view, jsonHandlers, uiProcessor);
    handler->handler(JsonFactory::pingJson());
    return app.exec();
}
