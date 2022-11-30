#ifndef REGISTERACTIONHANDLER_H
#define REGISTERACTIONHANDLER_H

#include <QObject>
#include <QJsonObject>
#include "actionhandler.h"
#include "jsonconstants.h"

class RegisterActionHandler : public ActionHandler
{
    Q_OBJECT
public:
    bool handle(QJsonObject json) override;
signals:
    void failedRegistration();
    void successfulRegistration(QString username);

};

#endif // REGISTERACTIONHANDLER_H
