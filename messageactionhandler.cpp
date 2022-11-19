#include "messageactionhandler.h"

MessageActionHandler::MessageActionHandler()
{

}

bool MessageActionHandler::handler(QJsonObject json)
{
    auto sender = json.take(FIELD_USERNAME);
    auto message = json.take(FIELD_PAYLOAD);
    qDebug() << sender << ": " << message;
    emit showMessage(message.toString(), sender.toString());
    return false;
}
