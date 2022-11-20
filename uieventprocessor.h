#ifndef UIEVENTPROCESSOR_H
#define UIEVENTPROCESSOR_H

#include <QObject>
#include "socketclient.h"

class UiEventProcessor : public QObject
{
    Q_OBJECT
public:
    explicit UiEventProcessor(SocketClient *client, QObject *parent = nullptr);
    void sendSignalToAppendMessage(QString message);

private:
    SocketClient *client = nullptr;

signals:
    void appendMessage(QString message);

public slots:
    void cppSlot(const QString &name, const QString &password) {
        qDebug() << "Trying to log in with name:" << name << "and pwd: " << password;
//        emit serverResponse("You can login now");
    }



};

#endif // UIEVENTPROCESSOR_H
