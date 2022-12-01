#include "jsonfactory.h"
#include <windows.h>

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

JsonObjectWrapper JsonFactory::sendMsgJson(QString message, QString type)
{
    JsonObjectWrapper content;
    content.insert(FIELD_ACTION, ACTION_MESSAGE);
    content.insert(FIELD_PAYLOAD, message);
    content.insert(FIELD_TYPE, type);
    // for pipes and mailslots
    content.insert("PID", QString::number(GetCurrentProcessId()));
    return content;
}

JsonObjectWrapper JsonFactory::sendJoinJson()
{
    JsonObjectWrapper content;
    content.insert(FIELD_ACTION, "JOIN");
    // for pipes and mailslots
    content.insert("PID", QString::number(GetCurrentProcessId()));
    return content;
}
