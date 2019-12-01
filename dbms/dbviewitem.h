#ifndef DBVIEWITEM_H
#define DBVIEWITEM_H

#include "dbtableitem.h"
class DBViewItem : public DBTableItem
{
  Q_OBJECT
public:
  DBViewItem(QString caption, QObject* parent = nullptr);
  virtual ~DBViewItem() override;

private:

  // LAbstractTreeItem interface
public:
  virtual int colCount() override;
  virtual QVariant colData(int column, int role) override;
  virtual bool setData(int column, QVariant value, int role) override;
  // DBObjectItem interface
public:
  virtual int type() override;
  virtual ActionResult insertMe() override;
  virtual ActionResult deleteMe() override;
};

#endif // DBVIEWITEM_H