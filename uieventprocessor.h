#ifndef UIEVENTPROCESSOR_H
#define UIEVENTPROCESSOR_H

#include <QObject>
#include "socketconnection.h"

class UiEventProcessor : public QObject
{
    Q_OBJECT
public:
    explicit UiEventProcessor(SocketConnection *client, QObject *parent = nullptr);
    void connectionFailed();

private:
    SocketConnection *connection = nullptr;

signals:
    void appendMessage(QString message);
    void showConnectionFailed();

public slots:
    void onRegisterClicked(const QString &name, const QString &password);
    void onLoginClicked(const QString &name, const QString &password);
    void onMessageSend(QString message);



};

#endif // UIEVENTPROCESSOR_H
