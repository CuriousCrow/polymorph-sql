#ifndef QDBTRIGGERITEM_H
#define QDBTRIGGERITEM_H

#include "qdbobjectitem.h"

class QDBTriggerItem : public QDBObjectItem
{
public:
  QDBTriggerItem(QString caption, QObject* parent = nullptr);
  virtual ~QDBTriggerItem() override;

  // LAbstractTreeItem interface
public:
  virtual int colCount() override;
  virtual QVariant colData(int column, int role) override;

  // QDBObjectItem interface
public:
  virtual bool loadChildren() override;
  virtual int type() override;
  
  // QDBObjectItem interface
public:
  virtual ActionResult insertMe() override;
  virtual ActionResult updateMe() override;
  virtual ActionResult deleteMe() override;
};

#endif // QDBTRIGGERITEM_H
