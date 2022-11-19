#ifndef MESSAGEACTIONHANDLER_H
#define MESSAGEACTIONHANDLER_H

#include <QObject>
#include <QJsonObject>
#include "actionhandler.h"
#include "jsonconstants.h"

class MessageActionHandler : public ActionHandler
{
    Q_OBJECT
public:
    MessageActionHandler();
    bool handler(QJsonObject json) override;
signals:
    void showMessage(QString msg, QString sender);
};

#endif // MESSAGEACTIONHANDLER_H
