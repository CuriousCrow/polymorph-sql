#ifndef DBSEQUENCEITEM_H
#define DBSEQUENCEITEM_H

#include "dbobjectitem.h"

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

  // DBObjectItem interface
public:
  virtual bool reloadChildren();
  virtual int type();

  // DBObjectItem interface
public:
  ActionResult insertMe();
  ActionResult updateMe();
  ActionResult deleteMe();
};

#endif // DBSEQUENCEITEM_H
