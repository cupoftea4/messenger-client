#include "messageactionhandler.h"
#include <QResource>
#include <QJsonArray>

MessageActionHandler::MessageActionHandler()
{

}

bool MessageActionHandler::handle(QJsonObject json)
{
    auto action = json[FIELD_ACTION].toString();
    if (action == ACTION_MESSAGE) {
        showMessage(json);
        return true;
    } else if (action == ACTION_CHAT_HISTORY) {
        QJsonArray chatHistory = json[FIELD_PAYLOAD].toArray();
        for (const auto &item : chatHistory) {
            QJsonObject obj = item.toObject();
            showMessage(obj);
        }
        return true;
    }
    return false;
}

void MessageActionHandler::showMessage(QJsonObject json)
{
    auto sender = json[FIELD_USERNAME].toString();
    auto message = json[FIELD_PAYLOAD].toString();
    auto type = json[FIELD_TYPE].toString();
    emit messageReceived(sender, message, type);
}
