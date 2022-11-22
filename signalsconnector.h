#ifndef SIGNALSCONNECTOR_H
#define SIGNALSCONNECTOR_H

#include <QObject>
#include <QQuickItem>
#include <QQuickView>
#include <QQmlContext>
#include "servereventservice.h"
#include "uieventprocessor.h"

class SignalsConnector : public QObject
{
    Q_OBJECT
public:
    explicit SignalsConnector(QObject *parent = nullptr);
    bool connect(QQuickView *view, ServerEventService *eventService, UiEventProcessor *uiProcessor);

private:
    void connectHandlers(QQuickView *view, ServerEventService *eventService);
    void connectUiProcessor(QQuickView *view, UiEventProcessor *uiProcessor);

    bool connectRegisterHandler(QQuickView *view, ActionHandler* handler);
    bool connectMessageHandler(QQuickView *view,  ActionHandler* handler);
    bool connectLoginHandler(QQuickView *view,  ActionHandler* handler);

    void connectActionButtons(QObject *root, UiEventProcessor *uiProcessor);
    void connectConnctionTypeButtons(QObject *root, UiEventProcessor *uiProcessor);


};

#endif // SIGNALSCONNECTOR_H
