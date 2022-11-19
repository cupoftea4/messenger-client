#include "signalsconnector.h"

SignalsConnector::SignalsConnector(QObject *parent)
    : QObject{parent}
{

}

bool SignalsConnector::connectAuthenticationForm(QObject *rootElement)
{
    QObject *button = rootElement->findChild<QObject*>("login_btn");
    if (button == nullptr)
        return false;

    QObject::connect(button, SIGNAL(qmlSignal(QString,QString)),
                        this, SLOT(cppSlot(QString,QString)));

    QObject::connect(this, SIGNAL(serverResponse(QString)),
                        button, SLOT(onServerResponse(QString)), Qt::QueuedConnection);
    emit serverResponse("I'm client1");
    return true;
}
