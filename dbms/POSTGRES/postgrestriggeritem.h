#ifndef POSTGRESTRIGGERITEM_H
#define POSTGRESTRIGGERITEM_H

#include <QObject>
#include "../qdbtriggeritem.h"

class PostgresTriggerItem : public QDBTriggerItem
{
  Q_OBJECT
public:
  PostgresTriggerItem(QString caption, QObject* parent = nullptr);

  // QDBObjectItem interface
public:
  virtual bool refresh() override;
  virtual bool insertMe() override;
  virtual bool updateMe() override;
  virtual bool deleteMe() override;
private:
  void setEventByName(QString event);

};

#endif // POSTGRESTRIGGERITEM_H
