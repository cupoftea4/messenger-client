#ifndef ACTIONHANDLER_H
#define ACTIONHANDLER_H

#include <QObject>

class ActionHandler : public QObject
{
public:
    ActionHandler();
    virtual bool handle(QJsonObject json) = 0;
};

#endif // ACTIONHANDLER_H
