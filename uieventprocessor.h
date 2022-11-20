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
    SocketClient *connection = nullptr;

signals:
    void appendMessage(QString message);

public slots:
    void onRegisterClicked(const QString &name, const QString &password);
    void onLoginClicked(const QString &name, const QString &password);
    void onMessageSend(QString message);



};

#endif // UIEVENTPROCESSOR_H
