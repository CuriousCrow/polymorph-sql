#ifndef QDBTRIGGERITEM_H
#define QDBTRIGGERITEM_H

#include "qdbobjectitem.h"

class QDBTriggerItem : public QDBObjectItem
{
public:
  QDBTriggerItem(QString caption, QUrl url, QObject* parent = nullptr);
  ~QDBTriggerItem();

  // LAbstractTreeItem interface
public:
  virtual int colCount();
  virtual QVariant colData(int column, int role);

  // QDBObjectItem interface
public:
  virtual bool loadChildren();
  virtual int type();
  
  // QDBObjectItem interface
public:
  virtual bool insertMe();
  virtual bool updateMe();
  virtual bool deleteMe();
};

#endif // QDBTRIGGERITEM_H
