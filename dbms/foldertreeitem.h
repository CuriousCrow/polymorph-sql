#ifndef FOLDERTREEITEM_H
#define FOLDERTREEITEM_H

#include "dbobjectitem.h"

class FolderTreeItem : public DBObjectItem
{
  Q_OBJECT
public:
  FolderTreeItem(QString urlName, QString caption, QObject* parent = nullptr);
  virtual ~FolderTreeItem() override;

  DBObjectItem::ItemType childrenType() const;
  void setChildrenType(DBObjectItem::ItemType childrenType);
signals:
  void reloadMe();
  // LAbstractTreeItem interface
public:
  virtual int colCount() override;
  virtual QVariant colData(int column, int role) override;
  virtual AppUrl objectUrl() override;

  // DBObjectItem interface
public:
  virtual bool reloadChildren() override;
  virtual int type() override;

private:
  QString _urlName;
  DBObjectItem::ItemType _childrenType = UnknownType;
};

#endif // FOLDERTREEITEM_H
