#ifndef QFOLDERTREEITEM_H
#define QFOLDERTREEITEM_H

#include "qdbobjectitem.h"

class FolderTreeItem : public DBObjectItem
{
  Q_OBJECT
public:
  FolderTreeItem(QString caption, QObject* parent = nullptr);
  virtual ~FolderTreeItem() override;

  DBObjectItem::ItemType childrenType() const;
  void setChildrenType(DBObjectItem::ItemType childrenType);
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
  DBObjectItem::ItemType _childrenType = UnknownType;

};

#endif // QFOLDERTREEITEM_H
