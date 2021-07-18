#ifndef LOCALEVENTNOTIFIER_H
#define LOCALEVENTNOTIFIER_H

#include <QEvent>
#include <QObject>
#include <QVariant>
#include <QMainWindow>

#define PARAM_MESSAGE "msg"

const QEvent::Type ShowObjectEvent = static_cast<QEvent::Type>(QEvent::User + 1);
const QEvent::Type CloseObjectEvent = static_cast<QEvent::Type>(QEvent::User + 2);
const QEvent::Type InfoMessageEvent = static_cast<QEvent::Type>(QEvent::User + 3);


class LocalEvent : public QEvent
{
public:
  LocalEvent(QEvent::Type type, QString url, QVariantMap params);

  QVariant param(QString name);
  QString url();
private:
  QVariantMap _params;
  QString _url;
};

class NotifiableWindow : public QMainWindow
{
  Q_OBJECT
public:
  NotifiableWindow(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

  // QObject interface
public:
  bool event(QEvent *event);
protected:
  virtual void localEvent(LocalEvent* event);
};

class LocalEventNotifier
{
public:
//  static LocalEventNotifier* instance();
  static void postLocalEvent(QEvent::Type type, QString url, QVariantMap params = QVariantMap());
private:
//  LocalEventNotifier();
//  static LocalEventNotifier* _singleton;
};

#endif // LOCALEVENTNOTIFIER_H
