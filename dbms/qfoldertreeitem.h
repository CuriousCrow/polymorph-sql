#ifndef QFOLDERTREEITEM_H
#define QFOLDERTREEITEM_H

#include "qdbobjectitem.h"

class QFolderTreeItem : public QDBObjectItem
{
  Q_OBJECT
public:
  QFolderTreeItem(QString caption, QObject* parent = nullptr);
  ~QFolderTreeItem();

  QDBObjectItem::ItemType childrenType() const;
  void setChildrenType(QDBObjectItem::ItemType childrenType);

  // LAbstractTreeItem interface
public:
  virtual int colCount();
  virtual QVariant colData(int column, int role);

  // QDBObjectItem interface
public:
  virtual bool loadChildren();
  virtual int type();

private:
  QDBObjectItem::ItemType _childrenType = UnknownType;
};

#endif // QFOLDERTREEITEM_H
