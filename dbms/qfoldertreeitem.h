#ifndef QFOLDERTREEITEM_H
#define QFOLDERTREEITEM_H

#include "qdbobjectitem.h"

class QFolderTreeItem : public QDBObjectItem
{
  Q_OBJECT
public:
  QFolderTreeItem(QString caption, QObject* parent = nullptr);
  virtual ~QFolderTreeItem() override;

  QDBObjectItem::ItemType childrenType() const;
  void setChildrenType(QDBObjectItem::ItemType childrenType);
signals:
  void reloadMe();
  // LAbstractTreeItem interface
public:
  virtual int colCount() override;
  virtual QVariant colData(int column, int role) override;

  // QDBObjectItem interface
public:
  virtual bool reloadChildren() override;
  virtual int type() override;

private:
  QDBObjectItem::ItemType _childrenType = UnknownType;

};

#endif // QFOLDERTREEITEM_H
