#ifndef UIEVENTPROCESSOR_H
#define UIEVENTPROCESSOR_H

#include <QObject>
#include "socketconnection.h"

class UiEventProcessor : public QObject
{
    Q_OBJECT
public:
    explicit UiEventProcessor(SocketConnection *connection, QObject *parent = nullptr);
    void connectionFailed();
    void disconnect();
private:
    SocketConnection *connection = nullptr;

signals:
    void appendMessage(QString message);
    void showConnectionFailed();

    void socketsConnected();
    void pipesConnected();
    void mailslotsConnected();

public slots:
    void onRegisterClicked(const QString &name, const QString &password);
    void onLoginClicked(const QString &name, const QString &password);
    void onMessageSend(QString message);

    void onSocketsConnectionClicked();
    void onPipesConnectionClicked();
    void onMailslotsConnectionClicked();


};

#endif // UIEVENTPROCESSOR_H
