#ifndef QDBPROCEDUREITEM_H
#define QDBPROCEDUREITEM_H

#include "qdbobjectitem.h"

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

  // QDBObjectItem interface
public:
  virtual bool reloadChildren();
  virtual int type();
};

#endif // QDBPROCEDUREITEM_H
