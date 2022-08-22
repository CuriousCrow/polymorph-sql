#ifndef DBPROCEDUREITEM_H
#define DBPROCEDUREITEM_H

#include "dbobjectitem.h"

class DBProcedureItem : public DBObjectItem
{
  Q_OBJECT
public:
  Q_INVOKABLE DBProcedureItem();
  ~DBProcedureItem() Q_DECL_OVERRIDE;

  // LAbstractTreeItem interface
public:
  virtual int colCount() const Q_DECL_OVERRIDE;
  virtual QVariant colData(int column, int role) const Q_DECL_OVERRIDE;

  // DBObjectItem interface
public:
  virtual bool reloadChildren() Q_DECL_OVERRIDE;
  virtual int type() const Q_DECL_OVERRIDE;
  virtual ActionResult deleteMe() override;
};

#endif // DBPROCEDUREITEM_H
