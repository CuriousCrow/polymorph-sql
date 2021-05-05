#include "localeventnotifier.h"
#include <QApplication>
#include <QWidget>
#include <QDebug>

//LocalEventNotifier* LocalEventNotifier::_singleton = nullptr;

//LocalEventNotifier *LocalEventNotifier::instance()
//{
//  if (!_singleton)
//    _singleton = new LocalEventNotifier();
//  return _singleton;
//}

void LocalEventNotifier::postLocalEvent(QEvent::Type type, QString url, QVariantMap params)
{
  LocalEvent event(type, url, params);
  foreach(QWidget* widget, QApplication::topLevelWidgets()) {
    if (widget->inherits("NotifiableWindow")) {
      qDebug() << "Local event to" << widget->objectName();
      QApplication::sendEvent(widget, &event);
    }
  }
}

//LocalEventNotifier::LocalEventNotifier()
//{
//}

LocalEvent::LocalEvent(QEvent::Type type, QString url, QVariantMap params)
  : QEvent(type), _params(params), _url(url)
{

}

QVariant LocalEvent::param(QString name)
{
    return _params.value(name);
}

QString LocalEvent::url()
{
  return _url;
}

NotifiableWindow::NotifiableWindow(QWidget *parent, Qt::WindowFlags flags)
  : QMainWindow(parent, flags)
{

}

bool NotifiableWindow::event(QEvent *event)
{
  if (event->type() > QEvent::User) {
    LocalEvent *localEvent = static_cast<LocalEvent*>(event);
    this->localEvent(localEvent);
    return true;
  }
  return QWidget::event(event);
}

void NotifiableWindow::localEvent(LocalEvent *event)
{
  Q_UNUSED(event)
  //By default do nothing
}
