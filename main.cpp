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

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    SignalsConnector tester;

    std::map<std::string, ActionHandler*> jsonHandlers;
//    RegisterActionHandler *registerHandler = new RegisterActionHandler();
    MessageActionHandler *messageHandler = new MessageActionHandler;
//    jsonHandlers[ACTION_REGISTER] = registerHandler;
    jsonHandlers[ACTION_MESSAGE] = messageHandler;


    QQuickView view;
    view.engine()->addImportPath("qrc:/qml/imports");
//    qmlRegisterType<SignalsConnector>("SignalsConnector", 1, 0, "SignalsConnector");

//    view.engine()->rootContext()->setContextProperty("MessageHandler", messageHandler);
    QQuickStyle::setStyle("Material");
    view.setSource(QUrl("qrc:/qml/content/Screen01.ui.qml"));
    if (!view.errors().isEmpty())
        return -1;
    view.show();
    QObject *root = view.rootObject();
//    tester.connectAuthenticationForm(root);

    SocketClient client = SocketClient("127.0.0.1", jsonHandlers);
    QString str = "Hey";
    client.sendMessage(str.toStdWString());

    QObject *element = root->findChild<QObject*>("login_btn");
    RegisterActionHandler *registerHandle1 = new RegisterActionHandler();
    view.engine()->rootContext()->setContextProperty("RegisterHandler", registerHandle1);
    registerHandle1->connectBtn(element);
//    QObject::connect(registerHandler, SIGNAL(RegisterHandler::failedRegistration()),
//                        elment, SLOT(onRegisterFail()), Qt::QueuedConnection);
    registerHandle1->handler(JsonFactory::registerJson("myname", "pashahd"));
    return app.exec();
}
