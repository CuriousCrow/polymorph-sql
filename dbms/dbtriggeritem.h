#ifndef DBTRIGGERITEM_H
#define DBTRIGGERITEM_H

#include "dbobjectitem.h"

class DBTriggerItem : public DBObjectItem
{
public:
  DBTriggerItem(QString caption, QObject* parent = nullptr);
  virtual ~DBTriggerItem() override;

  // LAbstractTreeItem interface
public:
  virtual int colCount() override;
  virtual QVariant colData(int column, int role) override;

  // DBObjectItem interface
public:
  virtual bool reloadChildren() override;
  virtual int type() override;
  
  // DBObjectItem interface
public:
  virtual ActionResult insertMe() override;
  virtual ActionResult updateMe() override;
  virtual ActionResult deleteMe() override;
};

#endif // DBTRIGGERITEM_H
