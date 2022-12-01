#include "messageactionhandler.h"
#include <QResource>

MessageActionHandler::MessageActionHandler()
{

}

bool MessageActionHandler::handle(QJsonObject json)
{
    auto sender = json.take(FIELD_USERNAME).toString();
    auto message = json.take(FIELD_PAYLOAD).toString();
    auto type = json.take(FIELD_TYPE).toString();
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
}
