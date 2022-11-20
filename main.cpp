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


//    UiEventProcessor *uiProcessor = new UiEventProcessor(client);


    QQuickView view;
    view.engine()->addImportPath("qrc:/qml/imports");
    QQuickStyle::setStyle("Material");
    view.setSource(QUrl("qrc:/qml/content/Screen01.ui.qml"));
    if (!view.errors().isEmpty()) {
        return -1;
    }
    view.show();

    SocketClient *client = new SocketClient("localhost", jsonHandlers);
    UiEventProcessor *uiProcessor = new UiEventProcessor(client);
    client->setMessageReceiver([uiProcessor](std::wstring msg) {
        qDebug() << "In lambda: " << QString::fromStdWString(msg);
        uiProcessor->sendSignalToAppendMessage(QString::fromStdWString(msg));
    });
    client->init();

    tester.connectSignals(view, jsonHandlers, uiProcessor);
    handler->handler(JsonFactory::pingJson());

    std::this_thread::sleep_for(50ms);
    QString str = "Hey111111111";
    client->sendMessage(str.toStdWString());
    return app.exec();
}
