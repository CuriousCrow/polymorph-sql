#ifndef DBSEQUENCE_H
#define DBSEQUENCE_H

#include "dbobjectitem.h"

class DBSequenceItem : public DBObjectItem
{
  Q_OBJECT
public:
  Q_INVOKABLE DBSequenceItem();
  virtual ~DBSequenceItem() Q_DECL_OVERRIDE;

  // LAbstractTreeItem interface
public:
  virtual int colCount() const Q_DECL_OVERRIDE;
  virtual QVariant colData(int column, int role) const Q_DECL_OVERRIDE;

  // DBObjectItem interface
public:
  virtual bool reloadChildren() Q_DECL_OVERRIDE;
  virtual int type() const Q_DECL_OVERRIDE;

  // DBObjectItem interface
public:
  ActionResult insertMe() Q_DECL_OVERRIDE;
  ActionResult updateMe() Q_DECL_OVERRIDE;
  ActionResult deleteMe() Q_DECL_OVERRIDE;

  virtual QString toDDL() const Q_DECL_OVERRIDE;
};

#endif // DBSEQUENCE_H
