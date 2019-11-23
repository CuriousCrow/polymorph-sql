#ifndef QDBVIEWITEM_H
#define QDBVIEWITEM_H

#include "qdbtableitem.h"

class QDBViewItem : public QDBTableItem
{
  Q_OBJECT
public:
  QDBViewItem(QString caption, QObject* parent = nullptr);
  virtual ~QDBViewItem() override;

private:

  // LAbstractTreeItem interface
public:
  virtual int colCount() override;
  virtual QVariant colData(int column, int role) override;
  virtual bool setData(int column, QVariant value, int role) override;
  // QDBObjectItem interface
public:
  virtual int type() override;
  virtual ActionResult insertMe() override;
  virtual ActionResult deleteMe() override;
};

#endif // QDBVIEWITEM_H
