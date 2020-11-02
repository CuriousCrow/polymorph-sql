#ifndef DBVIEWITEM_H
#define DBVIEWITEM_H

#include "dbtableitem.h"
class DBViewItem : public DBTableItem
{
  Q_OBJECT
public:
  DBViewItem(QString caption, QObject* parent = nullptr);
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
};

#endif // DBVIEWITEM_H
