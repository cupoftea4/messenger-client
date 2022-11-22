#ifndef SERVEREVENTSERVICE_H
#define SERVEREVENTSERVICE_H

#include <QObject>
#include <QJsonObject>
#include "actionhandler.h"
#include "jsonconstants.h"

using std::map;

class ServerEventService : public QObject
{
    Q_OBJECT
public:
    explicit ServerEventService(map<QString, ActionHandler *> *handlers, QObject *parent = nullptr);

    void handleEvent(QJsonObject json);
    void handleDisconnect(); // on lost connection with server
    map<QString, ActionHandler *> getHandlers();
private:
    map<QString, ActionHandler *> *actionHandles = nullptr;


signals:
    void showServerDisconnected();

};

#endif // SERVEREVENTSERVICE_H
