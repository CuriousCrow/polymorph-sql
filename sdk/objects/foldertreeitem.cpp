#include "foldertreeitem.h"
#include "appconst.h"
#include "appurl.h"
#include <QDebug>

FolderTreeItem::FolderTreeItem(QObject* parent):
  DBObjectItem("", parent)
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
    _urlName = typeName(_childrenType);
    setFieldValue(F_CAPTION, folderName(_childrenType));
}

QString FolderTreeItem::typeName(DBObjectItem::ItemType type)
{
    switch (type) {
    case DBObjectItem::Table:
      return FOLDER_TABLES;
    case DBObjectItem::SystemTable:
      return FOLDER_SYSTABLES;
    case DBObjectItem::View:
      return FOLDER_VIEWS;
    case DBObjectItem::Trigger:
      return FOLDER_TRIGGERS;
    case DBObjectItem::Sequence:
      return FOLDER_SEQUENCES;
    case DBObjectItem::Procedure:
      return FOLDER_PROCEDURES;
    default:
      return "unknown";
    }
}

QString FolderTreeItem::folderName(DBObjectItem::ItemType type)
{
    switch (type) {
    case DBObjectItem::Table:
      return tr("Tables");
    case DBObjectItem::SystemTable:
      return tr("System tables");
    case DBObjectItem::View:
      return tr("Views");
    case DBObjectItem::Sequence:
      return tr("Sequences");
    case DBObjectItem::Procedure:
      return tr("Procedures");
    case DBObjectItem::Trigger:
      return tr("Triggers");
    default:
      return "";
    }
}

AppUrl FolderTreeItem::objectUrl()
{
  AppUrl url = _parentUrl;
  url.cd(_urlName);
  return url;
}
