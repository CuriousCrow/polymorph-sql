#ifndef FOLDERTREEITEM_H
#define FOLDERTREEITEM_H

#include "dbobjectitem.h"

class FolderTreeItem : public DBObjectItem
{
  Q_OBJECT
public:
  FolderTreeItem(QString urlName, QString caption, QObject* parent = nullptr);
  virtual ~FolderTreeItem() Q_DECL_OVERRIDE;

  DBObjectItem::ItemType childrenType() const;
  void setChildrenType(DBObjectItem::ItemType childrenType);
signals:
  void reloadMe();
  // LAbstractTreeItem interface
public:
  virtual int colCount() const Q_DECL_OVERRIDE;
  virtual QVariant colData(int column, int role) const Q_DECL_OVERRIDE;
  virtual AppUrl objectUrl() Q_DECL_OVERRIDE;

  // DBObjectItem interface
public:
  virtual bool reloadChildren() Q_DECL_OVERRIDE;
  virtual int type() const Q_DECL_OVERRIDE;

private:
  QString _urlName;
  DBObjectItem::ItemType _childrenType = UnknownType;
};

#endif // FOLDERTREEITEM_H
