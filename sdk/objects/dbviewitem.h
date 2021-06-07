#ifndef DBVIEWITEM_H
#define DBVIEWITEM_H

#include "dbselectableitem.h"


class DBViewItem : public DBSelectableItem
{
  Q_OBJECT
public:
  Q_INVOKABLE DBViewItem();
  virtual ~DBViewItem() Q_DECL_OVERRIDE;

private:

  // LAbstractTreeItem interface
public:
  virtual int colCount() const Q_DECL_OVERRIDE;
  virtual QVariant colData(int column, int role) const Q_DECL_OVERRIDE;
  virtual bool setData(int column, QVariant value, int role) Q_DECL_OVERRIDE;
  // DBObjectItem interface
public:
  virtual int type() const Q_DECL_OVERRIDE;
  virtual ActionResult insertMe() Q_DECL_OVERRIDE;
  virtual ActionResult deleteMe() Q_DECL_OVERRIDE;

  virtual QString toDDL() const Q_DECL_OVERRIDE;
};

#endif // DBVIEWITEM_H
