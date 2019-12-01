#ifndef QDBSEQUENCEITEM_H
#define QDBSEQUENCEITEM_H

#include "qdbobjectitem.h"

class DBSequenceItem : public DBObjectItem
{
  Q_OBJECT
public:
  DBSequenceItem(QString caption, QObject* parent = nullptr);
  ~DBSequenceItem();

  // LAbstractTreeItem interface
public:
  virtual int colCount();
  virtual QVariant colData(int column, int role);

  // QDBObjectItem interface
public:
  virtual bool reloadChildren();
  virtual int type();

  // QDBObjectItem interface
public:
  ActionResult insertMe();
  ActionResult updateMe();
  ActionResult deleteMe();
};

#endif // QDBSEQUENCEITEM_H
