#include "servereventservice.h"

ServerEventService::ServerEventService(map<QString, ActionHandler *> *handlers, QObject *parent)
    : QObject{parent}
{
    this->actionHandles = handlers;
    qDebug() << "In serverEventService: is map empty?: " << (*actionHandles).size();
    for (auto& [handlerAction, handler] : *actionHandles) {
        qDebug() << handlerAction;
    }
}

void ServerEventService::handleEvent(QJsonObject json)
{
//    QString action = json.take(FIELD_ACTION).toString();
    qDebug() << "Trying to handle action";
    qDebug() << "In serverEventService: handleEvent(): is map empty?: " << (actionHandles == nullptr);
    if (actionHandles == nullptr) return;

    qDebug() << "Checked if empty" << actionHandles->size();
    return;
//    if (actionHandles->empty()) {
//        qDebug() << "Empty";
//        return;
//    }
//    qDebug() << "Checked if empty";
//    for (auto& [handlerAction, handler] : *actionHandles) {
//        qDebug() << handlerAction;
//    }
//    return;
//    if (actionHandles->find(action) != actionHandles->end()) {
//        qDebug() << "Found handler with action - " << action;
//        (*actionHandles)[action]->handler(json);
//    }
//    qDebug() << "NOT Found handler with action - " << action;
}

void ServerEventService::handleDisconnect()
{
    emit showServerDisconnected();
}

map<QString, ActionHandler *> ServerEventService::getHandlers()
{
    return *actionHandles;
}
