#ifndef DBPROCEDUREITEM_H
#define DBPROCEDUREITEM_H

#include "dbobjectitem.h"

class DBProcedureItem : public DBObjectItem
{
  Q_OBJECT
public:
  DBProcedureItem(QString caption, QObject* parent = nullptr);
  ~DBProcedureItem();

  // LAbstractTreeItem interface
public:
  virtual int colCount();
  virtual QVariant colData(int column, int role);

  // DBObjectItem interface
public:
  virtual bool reloadChildren();
  virtual int type();
};

#endif // DBPROCEDUREITEM_H
