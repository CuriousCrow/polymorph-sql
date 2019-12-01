#include "qfoldertreeitem.h"
#include "dbms/appconst.h"
#include <QUrl>
#include <QDebug>

FolderTreeItem::FolderTreeItem(QString caption, QObject* parent):
  DBObjectItem(caption, parent)
{
}

FolderTreeItem::~FolderTreeItem()
{

}

int FolderTreeItem::colCount()
{
  return 1;
}

QVariant FolderTreeItem::colData(int column, int role)
{
  Q_UNUSED(column)

  switch (role) {
  case Qt::DisplayRole:
    return QString("%1 (%2)").arg(fieldValue(F_CAPTION).toString(), QString::number(children().count()));
  default:
    return QVariant();
  }
}

bool FolderTreeItem::reloadChildren()
{
  emit reloadMe();
  return true;
}

int FolderTreeItem::type()
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
