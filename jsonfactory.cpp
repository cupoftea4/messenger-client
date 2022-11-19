#include "jsonfactory.h"

JsonFactory::JsonFactory()
{

}

JsonObjectWrapper JsonFactory::pingJson()
{
    JsonObjectWrapper content;
    content.insert("action", "PING");
    content.insert("payload", "");
    return content;
}

JsonObjectWrapper JsonFactory::loginJson(QString username, QString password)
{
    JsonObjectWrapper content;
    content.insert("action", "LOGIN");
    content.insert("username", username);
    content.insert("password", password);
    return content;
}

JsonObjectWrapper JsonFactory::registerJson(QString username, QString password)
{
    JsonObjectWrapper content;
    content.insert("action", "REGISTER");
    content.insert("username", username);
    content.insert("password", password);
    return content;
}

JsonObjectWrapper JsonFactory::sendMsgJson(QString message)
{
    JsonObjectWrapper content;
    content.insert("action", "MESSAGE");
    content.insert("payload", message);
    return content;
}



