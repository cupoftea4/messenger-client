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
        auto sender = json[FIELD_USERNAME].toString();
        auto message = json[FIELD_PAYLOAD].toString();
        auto type = json[FIELD_TYPE].toString();
        qDebug() << message.mid(38);
        if (type == "IMAGE") {
            QResource::registerResource(message.mid(38));
            emit messageReceived(sender, message, type);
            return true;
            // handle image url
        }
        qDebug() << sender << ": " << message;
        emit messageReceived(sender, message, type);
        return false;
    } else {
        QJsonArray chatHistory = json[FIELD_PAYLOAD].toArray();
        for (const auto &item : chatHistory) {
            QJsonObject obj = item.toObject();
            auto sender = obj[FIELD_USERNAME].toString();
            auto message = obj[FIELD_PAYLOAD].toString();
            emit messageReceived(sender, message, "TEXT");
        }
        return true;
    }

}
