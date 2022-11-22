#ifndef QUICKVIEWWRAPPER_H
#define QUICKVIEWWRAPPER_H

#include <QQuickView>
#include "uieventprocessor.h"

class QuickViewWrapper : public QQuickView
{
public:
    QuickViewWrapper(UiEventProcessor *  uiProcessor);

    bool event(QEvent *event) override;
private:
    UiEventProcessor * uiProcessor = nullptr;
};

#endif // QUICKVIEWWRAPPER_H
