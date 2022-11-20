#include "messageactionhandler.h"

MessageActionHandler::MessageActionHandler()
{

}

bool MessageActionHandler::handler(QJsonObject json)
{
    auto sender = json.take(FIELD_USERNAME).toString();
    auto message = json.take(FIELD_PAYLOAD).toString();
    qDebug() << sender << ": " << message;
    emit messageReceived(message, sender);
    return false;
}
