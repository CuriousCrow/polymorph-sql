#ifndef DBPROCEDURE_H
#define DBPROCEDURE_H

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
  virtual QString dropDDL() const Q_DECL_OVERRIDE;
};

#endif // DBPROCEDURE_H
