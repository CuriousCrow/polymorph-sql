#include "localeventnotifier.h"
#include <QApplication>
#include <QWidget>
#include <QDebug>

void LocalEventNotifier::postLocalEvent(QEvent::Type type, QString url, QVariantMap params)
{
  qDebug() << "Local event registered:" << type;
  LocalEvent event(type, url, params);
  foreach(QWidget* widget, QApplication::topLevelWidgets()) {
    if (widget->isVisible() && (widget->inherits("NotifiableWindow") || widget->inherits("NotifiableDialog"))) {
      qDebug() << "Local event to" << widget->objectName();
      QApplication::sendEvent(widget, &event);
    }
  }
}

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


NotifiableDialog::NotifiableDialog(QWidget *parent, Qt::WindowFlags f) :
  QDialog(parent, f)
{
}

bool NotifiableDialog::event(QEvent *event)
{
  if (event->type() > QEvent::User) {
    LocalEvent *localEvent = static_cast<LocalEvent*>(event);
    this->localEvent(localEvent);
    return true;
  }
  return QWidget::event(event);
}

void NotifiableDialog::localEvent(LocalEvent *event)
{
  Q_UNUSED(event)
  //By default do nothing
}
