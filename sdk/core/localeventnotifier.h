#ifndef LOCALEVENTNOTIFIER_H
#define LOCALEVENTNOTIFIER_H

#include <QEvent>
#include <QObject>
#include <QVariant>
#include <QMainWindow>
#include <QDialog>

#define PARAM_MESSAGE "msg"

const QEvent::Type ShowObjectEvent = static_cast<QEvent::Type>(QEvent::User + 1);
const QEvent::Type CloseObjectEvent = static_cast<QEvent::Type>(QEvent::User + 2);
const QEvent::Type InfoMessageEvent = static_cast<QEvent::Type>(QEvent::User + 3);
const QEvent::Type ItemDeleteEvent = static_cast<QEvent::Type>(QEvent::User + 4);
const QEvent::Type DbSchemaChangeEvent = static_cast<QEvent::Type>(QEvent::User + 5);


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

class NotifiableDialog : public QDialog
{
  Q_OBJECT
public:
  NotifiableDialog(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());

  // QObject interface
public:
  virtual bool event(QEvent *event) override;
protected:
  virtual void localEvent(LocalEvent* event);
};

class LocalEventNotifier
{
public:
  static void postLocalEvent(QEvent::Type type, QString url, QVariantMap params = QVariantMap());
};

#endif // LOCALEVENTNOTIFIER_H
