#include "servereventservice.h"

ServerEventService::ServerEventService(map<QString, ActionHandler *> handlers, QObject *parent)
    : QObject{parent}
{
    this->actionHandles = handlers;
}

void ServerEventService::handleEvent(QJsonObject json)
{
    QString action = json[FIELD_ACTION].toString();

    if (actionHandles.find(action) != actionHandles.end()) {
        actionHandles[action]->handle(json);
    }
    if (action == "BACKUP") {
        actionHandles[ACTION_MESSAGE]->handle(json);
    }
}

void ServerEventService::handleDisconnect()
{
    emit showServerDisconnected();
}

map<QString, ActionHandler *> ServerEventService::getHandlers()
{
    return actionHandles;
}
