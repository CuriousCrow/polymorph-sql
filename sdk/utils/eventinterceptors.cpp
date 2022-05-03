#include "eventinterceptors.h"
#include <QDebug>



SimpleEventInterceptor::SimpleEventInterceptor(QObject* parent) : QObject(parent)
{
}

void SimpleEventInterceptor::addEventType(QEvent::Type type)
{
  _eventTypes.append(type);
}

bool SimpleEventInterceptor::eventFilter(QObject* watched, QEvent* event)
{
//  qDebug() << "Event:" << event->type();
  if (_eventTypes.contains(event->type())) {
    qDebug() << "Event" << event->type() << "intercepted from" << watched->objectName();
    emit onEvent(event->type());
  }
  return false;
}
