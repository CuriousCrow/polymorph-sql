#ifndef DBTRIGGERITEM_H
#define DBTRIGGERITEM_H

#include "dbobjectitem.h"

class DBTriggerItem : public DBObjectItem
{
  Q_OBJECT
public:
  Q_INVOKABLE DBTriggerItem();
  virtual ~DBTriggerItem() Q_DECL_OVERRIDE;

  // LAbstractTreeItem interface
public:
  virtual int colCount() const Q_DECL_OVERRIDE;
  virtual QVariant colData(int column, int role) const Q_DECL_OVERRIDE;

  // DBObjectItem interface
public:
  virtual bool reloadChildren() Q_DECL_OVERRIDE;
  virtual int type() const override;
  
  // DBObjectItem interface
public:
  virtual ActionResult insertMe() Q_DECL_OVERRIDE;
  virtual ActionResult updateMe() Q_DECL_OVERRIDE;
  virtual ActionResult deleteMe() Q_DECL_OVERRIDE;
};

#endif // DBTRIGGERITEM_H
