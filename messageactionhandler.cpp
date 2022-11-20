#include "messageactionhandler.h"

MessageActionHandler::MessageActionHandler()
{

}

bool MessageActionHandler::handler(QJsonObject json)
{
//    emit messageReceived("Amy", "my message i sent");
//    emit messageReceived("Amy1", "ur message u sent");
//    emit messageReceived("Amy1", "ur message u sent 1");
//    emit messageReceived("Amy1", "ur message u sent 2");
//    emit messageReceived("Amy1", "ur message u sent 3");
//    emit messageReceived("Amy1", "ur message u sent 4");
//    emit messageReceived("Amy1", "ur message u sent 5");
//    emit messageReceived("Amy1", "ur message u sent 2");
//    emit messageReceived("Amy1", "ur message u sent 3");
//    emit messageReceived("Amy", "ur message u sent 4");
//    emit messageReceived("Amy1", "ur message u sent 5 ur message u sent 5 ur message u sent 5");
    auto sender = json.take(FIELD_USERNAME).toString();
    auto message = json.take(FIELD_PAYLOAD).toString();
    qDebug() << sender << ": " << message;
    emit messageReceived(message, sender);
    return false;
}
