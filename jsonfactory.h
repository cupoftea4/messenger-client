#ifndef JSONFACTORY_H
#define JSONFACTORY_H
#include <QJsonObject>
#include <QJsonDocument>
#include "jsonconstants.h"

using std::string;

class JsonObjectWrapper: public QJsonObject {
public:
    char *c_str() {
        QJsonDocument document;
        document.setObject(*this);
        QByteArray bytes = document.toJson(QJsonDocument::Indented);
        std::string jsonString = bytes.toStdString();
        char *cstr = new char[jsonString.length() + 1];
        strncpy(cstr, jsonString.c_str(), jsonString.length() + 1);
        return cstr;
    };
};

class JsonFactory
{
public:
    static JsonObjectWrapper pingJson();
    static JsonObjectWrapper loginJson(QString username, QString password);
    static JsonObjectWrapper registerJson(QString username, QString password);
    static JsonObjectWrapper sendMsgJson(QString message);
};

#endif // JSONFACTORY_H
