#ifndef SIGNALSCONNECTOR_H
#define SIGNALSCONNECTOR_H

#include <QObject>
#include <QQuickItem>
#include <QQuickView>
#include <QQmlContext>
#include "actionhandler.h"
#include "uieventprocessor.h"

class SignalsConnector : public QObject
{
    Q_OBJECT
public:
    explicit SignalsConnector(QObject *parent = nullptr);
    bool connectSignals(QQuickView& view, std::map<std::string, ActionHandler*> handlers, UiEventProcessor *uiProcessor);
private:
    bool connectAuthentication(QQuickView& view, std::map<std::string, ActionHandler*> handlers, UiEventProcessor *uiProcessor);

signals:
    void serverResponse(QString res);

};

#endif // SIGNALSCONNECTOR_H
