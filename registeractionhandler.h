#ifndef REGISTERACTIONHANDLER_H
#define REGISTERACTIONHANDLER_H

#include <QObject>
#include <QJsonObject>
#include "actionhandler.h"

class RegisterActionHandler :  public QObject
{
    Q_OBJECT
public:
     explicit RegisterActionHandler(QObject *parent = nullptr);
//    RegisterActionHandler(QObject *obj);
    bool handler(QJsonObject json) ;
    void connectBtn(QObject *obj);
signals:
    void failedRegistration();
    void successfulRegistration(QString username);
};

#endif // REGISTERACTIONHANDLER_H
