#include "jsonfactory.h"

JsonObjectWrapper JsonFactory::pingJson()
{
    JsonObjectWrapper content;
    content.insert(FIELD_ACTION, ACTION_PING);
    content.insert(FIELD_PAYLOAD, "");
    return content;
}

JsonObjectWrapper JsonFactory::loginJson(QString username, QString password)
{
    JsonObjectWrapper content;
    content.insert(FIELD_ACTION, ACTION_LOGIN);
    content.insert(FIELD_USERNAME, username);
    content.insert(FIELD_PASSWORD, password);
    return content;
}

JsonObjectWrapper JsonFactory::registerJson(QString username, QString password)
{
    JsonObjectWrapper content;
    content.insert(FIELD_ACTION, ACTION_REGISTER);
    content.insert(FIELD_USERNAME, username);
    content.insert(FIELD_PASSWORD, password);
    return content;
}

JsonObjectWrapper JsonFactory::sendMsgJson(QString message)
{
    JsonObjectWrapper content;
    content.insert(FIELD_ACTION, ACTION_MESSAGE);
    content.insert(FIELD_PAYLOAD, message);
    return content;
}
