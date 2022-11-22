#include <QGuiApplication>
#include "messengerconfiguration.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    MessengerConfiguration config;
    config.init();

    return app.exec();
}


