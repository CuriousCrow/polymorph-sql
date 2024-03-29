#ifndef FOLDERTREEITEM_H
#define FOLDERTREEITEM_H

#include "dbobjectitem.h"
#include "core/core.h"
#include "core/dependencycontainer.h"

class FolderTreeItem : public DBObjectItem
{
  Q_OBJECT
public:
  FolderTreeItem(QObject* parent = nullptr);
  virtual ~FolderTreeItem() Q_DECL_OVERRIDE;

  DBObjectItem::ItemType childrenType() const;
  void setChildrenType(DBObjectItem::ItemType childrenType);

  INJECT(Core*, core);

protected:
  QString typeName(DBObjectItem::ItemType type);
  virtual QString folderName(DBObjectItem::ItemType type);
  virtual void loadChildren();

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
  void loadTableItems();
  void loadViewItems();
  void loadSystemTableItems();
  QString _urlName;
  DBObjectItem::ItemType _childrenType = UnknownType;
};

#endif // FOLDERTREEITEM_H
