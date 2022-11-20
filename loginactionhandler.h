#ifndef LOGINACTIONHANDLER_H
#define LOGINACTIONHANDLER_H

#include <QObject>
#include <QJsonObject>
#include "actionhandler.h"
#include "jsonconstants.h"

class LoginActionHandler : public ActionHandler
{
    Q_OBJECT
public:
    LoginActionHandler();
    bool handler(QJsonObject json) override;
signals:
    void failedLogin();
    void successfulLogin(QString username);
};

#endif // LOGINACTIONHANDLER_H
