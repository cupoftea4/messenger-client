#ifndef CONNECTIONSERVICE_H
#define CONNECTIONSERVICE_H

#include <QObject>

class ConnectionService : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionService(QObject *parent = nullptr);

signals:

};

#endif // CONNECTIONSERVICE_H
