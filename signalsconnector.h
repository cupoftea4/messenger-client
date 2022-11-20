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
    bool connectSignals(QQuickView& view, std::map<QString, ActionHandler*> handlers, UiEventProcessor *uiProcessor);
private:
    bool connectRegisterHandler(QQuickView& view, ActionHandler* handler, UiEventProcessor *uiProcessor);
    bool connectMessageHandler(QQuickView& view,  ActionHandler* handler, UiEventProcessor *uiProcessor);
    bool connectLoginHandler(QQuickView& view,  ActionHandler* handler, UiEventProcessor *uiProcessor);

signals:
    void serverResponse(QString res);

};

#endif // SIGNALSCONNECTOR_H
