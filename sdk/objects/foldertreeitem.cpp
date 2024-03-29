#include "foldertreeitem.h"
#include "appconst.h"
#include "appurl.h"
#include "dbtableitem.h"
#include "dbview.h"
#include "core/core.h"

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
  deleteChildren();
  loadChildren();
  emit reloadMe();
  return true;
}

int FolderTreeItem::type() const
{
    return Folder;
}

void FolderTreeItem::loadTableItems()
{
    qDebug() << "loadTableItems()";
    QStringList tableNames = QSqlDatabase::database(connectionName()).tables(QSql::Tables);
    foreach (QString name, tableNames){
      DBTableItem* tableItem = _core->dependencyForDriver<DBTableItem>(driverName());
      tableItem->setParent(this);
      tableItem->setFieldValue(F_CAPTION, name);
      tableItem->setParentUrl(objectUrl());
    }
}

void FolderTreeItem::loadViewItems()
{
    qDebug() << "loadViewItems()";
    QStringList tableNames = QSqlDatabase::database(connectionName()).tables(QSql::Views);
    foreach (QString name, tableNames){
      DBViewItem* viewItem = _core->dependencyForDriver<DBViewItem>(driverName());
      viewItem->setParent(this);
      viewItem->setFieldValue(F_CAPTION, name);
      viewItem->setParentUrl(objectUrl());
    }
}

void FolderTreeItem::loadSystemTableItems()
{
    qDebug() << "loadSystemTableItems";
    QStringList tableNames = QSqlDatabase::database(connectionName()).tables(QSql::SystemTables);
    foreach (QString name, tableNames){
      DBTableItem* tableItem = _core->dependencyForDriver<DBTableItem>(driverName());
      tableItem->setSystem(true);
      tableItem->setParent(this);
      tableItem->setFieldValue(F_CAPTION, name);
      tableItem->setParentUrl(objectUrl());
    }
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
    case DBObjectItem::UserType:
      return FOLDER_USER_TYPE;
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
    case DBObjectItem::UserType:
      return tr("User types");
    default:
      return "";
    }
}

void FolderTreeItem::loadChildren()
{
    switch(_childrenType) {
    case DBObjectItem::Table:
        loadTableItems();
        break;
    case DBObjectItem::View:
        loadViewItems();
        break;
    case DBObjectItem::SystemTable:
        loadSystemTableItems();
        break;
    default:
        qWarning() << "loadChildren for type is not implemented yet" << _childrenType;
    }
}

AppUrl FolderTreeItem::objectUrl()
{
  AppUrl url = _parentUrl;
  url.cd(_urlName);
  return url;
}
