#include "foldertreeitem.h"
#include "dbms/appconst.h"
#include "appurl.h"
#include <QDebug>

FolderTreeItem::FolderTreeItem(QString urlName, QString caption, QObject* parent):
  DBObjectItem(caption, parent), _urlName(urlName)
{
}

FolderTreeItem::~FolderTreeItem()
{

}

int FolderTreeItem::colCount() const
{
  return 1;
}

QVariant FolderTreeItem::colData(int column, int role) const
{
  Q_UNUSED(column)

  switch (role) {
  case Qt::DisplayRole:
    return QString("%1 (%2)").arg(caption(), QString::number(children().count()));
  default:
    return QVariant();
  }
}

bool FolderTreeItem::reloadChildren()
{
  emit reloadMe();
  return true;
}

int FolderTreeItem::type() const
{
  return Folder;
}

DBObjectItem::ItemType FolderTreeItem::childrenType() const
{
  return _childrenType;
}

void FolderTreeItem::setChildrenType(DBObjectItem::ItemType childrenType)
{
  _childrenType = childrenType;
}

AppUrl FolderTreeItem::objectUrl()
{
  AppUrl url = _parentUrl;
  url.cd(_urlName);
  return url;
}
