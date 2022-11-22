#include "quickviewwrapper.h"

QuickViewWrapper::QuickViewWrapper(UiEventProcessor *  uiProcessor) : QQuickView()
{
    this->uiProcessor = uiProcessor;
}

bool QuickViewWrapper::event(QEvent *event)
{
    if (event->type() == QEvent::Close) {
        if (uiProcessor != nullptr) {
            uiProcessor->disconnect();
        }
        qDebug() << "Closed the window";
    }
    return QQuickView::event(event);
}
