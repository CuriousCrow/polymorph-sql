#ifndef QDBPROCEDUREITEM_H
#define QDBPROCEDUREITEM_H

#include "qdbobjectitem.h"

class QDBProcedureItem : public QDBObjectItem
{
  Q_OBJECT
public:
  QDBProcedureItem(QString caption, QObject* parent = nullptr);
  ~QDBProcedureItem();

  // LAbstractTreeItem interface
public:
  virtual int colCount();
  virtual QVariant colData(int column, int role);

  // QDBObjectItem interface
public:
  virtual bool loadChildren();
  virtual int type();
};

#endif // QDBPROCEDUREITEM_H
