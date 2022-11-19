#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include <QQuickStyle>
#include "signalsconnector.h"
#include "socketclient.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    SignalsConnector tester;

    QQuickView view;
    view.engine()->addImportPath("qrc:/qml/imports");
    qmlRegisterType<SignalsConnector>("SignalsConnector", 1, 0, "SignalsConnector");
    view.engine()->rootContext()->setContextProperty("SignalsConnector", &tester);
    QQuickStyle::setStyle("Material");
    view.setSource(QUrl("qrc:/qml/content/Screen01.ui.qml"));
    if (!view.errors().isEmpty())
        return -1;
    view.show();
    QObject *root = view.rootObject();
    tester.connectAuthenticationForm(root);

    SocketClient client = SocketClient("127.0.0.1");
    QString str = "Hey111111111";
    client.sendMessage(str.toStdWString());

    return app.exec();
}
