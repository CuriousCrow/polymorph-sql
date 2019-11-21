#include "qfoldertreeitem.h"
#include "dbms/appconst.h"
#include <QUrl>
#include <QDebug>

QFolderTreeItem::QFolderTreeItem(QString caption, QObject* parent):
  QDBObjectItem(caption, parent)
{
}

QFolderTreeItem::~QFolderTreeItem()
{

}

int QFolderTreeItem::colCount()
{
  return 1;
}

QVariant QFolderTreeItem::colData(int column, int role)
{
  Q_UNUSED(column)

  switch (role) {
  case Qt::DisplayRole:
    return QString("%1 (%2)").arg(fieldValue(F_CAPTION).toString(), QString::number(children().count()));
  default:
    return QVariant();
  }
}

bool QFolderTreeItem::loadChildren()
{
  return true;
}

int QFolderTreeItem::type()
{
  return Folder;
}

QDBObjectItem::ItemType QFolderTreeItem::childrenType() const
{
  return _childrenType;
}

void QFolderTreeItem::setChildrenType(QDBObjectItem::ItemType childrenType)
{
  _childrenType = childrenType;
}

//QUrl QFolderTreeItem::objectUrl()
//{
//  QUrl url = QDBObjectItem::objectUrl();
//  url.setPath("/" + fieldValue(F_CAPTION).toString());
//  return url;
//}
