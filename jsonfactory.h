#ifndef JSONFACTORY_H
#define JSONFACTORY_H
#include <QJsonObject>
#include <QJsonDocument>

using std::string;

class JsonObjectWrapper: public QJsonObject {
public:
    char* c_str() {
        QJsonDocument document;
        document.setObject(*this);
        QByteArray bytes = document.toJson(QJsonDocument::Indented);
        return bytes.data();
    };
};

class JsonFactory
{
public:
    JsonFactory();
    static JsonObjectWrapper pingJson();
    static JsonObjectWrapper loginJson(QString username, QString password);
    static JsonObjectWrapper registerJson(QString username, QString password);
    static JsonObjectWrapper sendMsgJson(QString message);
};

#endif // JSONFACTORY_H
