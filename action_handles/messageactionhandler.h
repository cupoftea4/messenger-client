#ifndef MESSAGEACTIONHANDLER_H
#define MESSAGEACTIONHANDLER_H

#include <QObject>
#include <QJsonObject>
#include "action_handles/actionhandler.h"
#include "jsonconstants.h"

class MessageActionHandler : public ActionHandler
{
    Q_OBJECT
public:
    MessageActionHandler();
    bool handle(QJsonObject json) override;
signals:
    void messageReceived(QString sender, QString msg, QString type);
};

#endif // MESSAGEACTIONHANDLER_H
