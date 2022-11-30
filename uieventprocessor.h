#ifndef UIEVENTPROCESSOR_H
#define UIEVENTPROCESSOR_H

#include <QObject>
#include "connectionprovider.h"
#include <windows.h>
#include "connectins/connection.h"

class UiEventProcessor : public QObject
{
    Q_OBJECT
public:
    explicit UiEventProcessor(ConnectionProvider *provider, QObject *parent = nullptr);
    ~UiEventProcessor();

signals:
    void socketsConnected();
    void mailslotsConnected(QString);

    void connectionFailed();

public slots:
    void onRegisterClicked(const QString &name, const QString &password);
    void onLoginClicked(const QString &name, const QString &password);
    void onMessageSend(QString message);

    void onSocketsConnectionClicked();
    void onMailslotsConnectionClicked();

private:
    ConnectionProvider *connectionProvider = nullptr;


};

#endif // UIEVENTPROCESSOR_H
