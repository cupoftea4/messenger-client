#ifndef REGISTERACTIONHANDLER_H
#define REGISTERACTIONHANDLER_H

#include <QObject>
#include <QJsonObject>
#include "actionhandler.h"

class RegisterActionHandler : public ActionHandler
{
    Q_OBJECT
public:
//    RegisterActionHandler(QObject *obj);
    bool handler(QJsonObject json) ;
signals:
    void failedRegistration();

};

#endif // REGISTERACTIONHANDLER_H
