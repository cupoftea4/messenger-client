#ifndef UIEVENTPROCESSOR_H
#define UIEVENTPROCESSOR_H

#include <QObject>
#include "socketclient.h"

class UiEventProcessor : public QObject
{
    Q_OBJECT
public:
    explicit UiEventProcessor(SocketClient *client, QObject *parent = nullptr);

private:
    SocketClient *client = nullptr;

signals:
    void appendMessage(QString message);

public slots:
    void onRegisterClicked(const QString &name, const QString &password) {
        qDebug() << "Trying to register in with name:" << name << "and pwd: " << password;
    }
    void onLoginClicked(const QString &name, const QString &password) {
        qDebug() << "Trying to login in with name:" << name << "and pwd: " << password;
    }
    void onMessageSend(QString message);



};

#endif // UIEVENTPROCESSOR_H
