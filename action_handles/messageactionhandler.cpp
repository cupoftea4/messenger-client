#include "messageactionhandler.h"

MessageActionHandler::MessageActionHandler()
{

}

bool MessageActionHandler::handle(QJsonObject json)
{
    auto sender = json.take(FIELD_USERNAME).toString();
    auto message = json.take(FIELD_PAYLOAD).toString();
    qDebug() << sender << ": " << message;
    emit messageReceived(sender, message);
    return false;
}