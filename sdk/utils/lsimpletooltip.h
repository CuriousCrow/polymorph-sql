#ifndef LSIMPLETOOLTIP_H
#define LSIMPLETOOLTIP_H

#include <QObject>
#include <QLabel>
#include <QTimer>

class HelpLookupProvider
{
public:
  virtual ~HelpLookupProvider();
  virtual QString lookup(QString keyword) = 0;
};

class LSimpleTooltip : public QLabel
{
public:
  LSimpleTooltip(QWidget* parent);
  void setWidget(QWidget* widget);
  void setDuration(int sec);
  void setLookupProvider(HelpLookupProvider* provider);
private:
  QTimer* _showTimer;
  int _margin = 5;
  int _secDuration = 0;
  HelpLookupProvider* _lookupProvider = nullptr;
  // QWidget interface
protected:
  virtual void paintEvent(QPaintEvent *event);
  // QObject interface
public:
  virtual bool eventFilter(QObject *watched, QEvent *event);
  virtual bool event(QEvent *event);
public slots:
  void popup(QString keyword, QPoint globalPos);
};

#endif // LSIMPLETOOLTIP_H
