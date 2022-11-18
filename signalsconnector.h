#ifndef SIGNALSCONNECTOR_H
#define SIGNALSCONNECTOR_H

#include <QObject>
#include <QQuickItem>

class SignalsConnector : public QObject
{
    Q_OBJECT
public:
    explicit SignalsConnector(QObject *parent = nullptr);
    bool connectAuthenticationForm(QObject * rootElement);
public slots:
    void cppSlot(const QString &name, const QString &password) {
        qDebug() << "Trying to log in with name:" << name << "and pwd: " << password;
        emit serverResponse("You can login now");
    }

signals:
    void serverResponse(QString res);

};

#endif // SIGNALSCONNECTOR_H
