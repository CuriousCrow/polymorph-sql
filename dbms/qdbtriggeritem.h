#ifndef QDBTRIGGERITEM_H
#define QDBTRIGGERITEM_H

#include "qdbobjectitem.h"

class DBTriggerItem : public DBObjectItem
{
public:
  DBTriggerItem(QString caption, QObject* parent = nullptr);
  virtual ~DBTriggerItem() override;

  // LAbstractTreeItem interface
public:
  virtual int colCount() override;
  virtual QVariant colData(int column, int role) override;

  // QDBObjectItem interface
public:
  virtual bool reloadChildren() override;
  virtual int type() override;
  
  // QDBObjectItem interface
public:
  virtual ActionResult insertMe() override;
  virtual ActionResult updateMe() override;
  virtual ActionResult deleteMe() override;
};

#endif // QDBTRIGGERITEM_H
