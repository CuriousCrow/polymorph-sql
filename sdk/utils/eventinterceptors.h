#ifndef EVENTINTERCEPTORS_H
#define EVENTINTERCEPTORS_H

#include <QObject>
#include <QEvent>

class SimpleEventInterceptor : public QObject
{
    Q_OBJECT
public:
    SimpleEventInterceptor(QObject* parent = Q_NULLPTR);
    void addEventType(QEvent::Type type);
signals:
    void onEvent(QEvent::Type type);
private:
    QList<QEvent::Type> _eventTypes;

    // QObject interface
public:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // EVENTINTERCEPTORS_H
