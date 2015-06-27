#ifndef QDBTRIGGERITEM_H
#define QDBTRIGGERITEM_H

#include "qdbobjectitem.h"

class QDBTriggerItem : public QDBObjectItem
{
public:
  QDBTriggerItem(QString caption, QObject* parent = 0);
  ~QDBTriggerItem();

  // LAbstractTreeItem interface
public:
  virtual int colCount();
  virtual QVariant colData(int column, int role);

  // QDBObjectItem interface
public:
  virtual bool loadChildren();
  virtual int type();
};

#endif // QDBTRIGGERITEM_H
