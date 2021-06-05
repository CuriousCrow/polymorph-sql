#include "firebirdplugin.h"
#include "sdk/objects/appconst.h"
#include "firebirdfolderitem.h"
#include "firebirddatabase.h"
#include "firebirdtable.h"


QString FirebirdPlugin::driver()
{
  return DRIVER_FIREBIRD;
}

DBDatabaseItem *FirebirdPlugin::newDatabaseItem(QString caption, QObject *parent)
{
  Q_UNUSED(parent)
  return new FirebirdDatabase(caption);
}

DBTableItem *FirebirdPlugin::newTableItem(QString caption, QObject *parent)
{
  return new FirebirdTable(caption, parent);
}

DBViewItem *FirebirdPlugin::newViewItem(QString caption, QObject *parent)
{
  return new DBViewItem(caption, parent);
}

DBProcedureItem *FirebirdPlugin::newProcedureItem(QString caption, QObject *parent)
{
  return new DBProcedureItem(caption, parent);
}

DBSequenceItem *FirebirdPlugin::newSequenceItem(QString caption, QObject *parent)
{
  return new DBSequenceItem(caption, parent);
}

DBTriggerItem *FirebirdPlugin::newTriggerItem(QString caption, QObject *parent)
{
    return new DBTriggerItem(caption, parent);
}

FolderTreeItem *FirebirdPlugin::newFolderItem(QObject *parent)
{
    FolderTreeItem* folder = new FirebirdFolderItem(parent);
    return folder;
}

AbstractDatabaseEditForm *FirebirdPlugin::formByType(DBObjectItem::ItemType type)
{
  Q_UNUSED(type)
  return nullptr;
}

QList<DBObjectItem::ItemType> FirebirdPlugin::supportedTypes()
{
  QList<DBObjectItem::ItemType> types;
  types.append(DBObjectItem::Table);
  types.append(DBObjectItem::View);
  types.append(DBObjectItem::Sequence);
  types.append(DBObjectItem::Procedure);
  types.append(DBObjectItem::Trigger);
  return types;
}

QString FirebirdPlugin::folderName(DBObjectItem::ItemType type)
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

void FirebirdPlugin::loadTables(FolderTreeItem *folderItem)
{
  QStringList tableNames = QSqlDatabase::database(folderItem->connectionName()).tables();
  foreach (QString name, tableNames){
    DBTableItem* tableItem = newTableItem(name, folderItem);
    tableItem->setParentUrl(folderItem->objectUrl());
  }
}

void FirebirdPlugin::loadViews(FolderTreeItem *folderItem)
{
  QStringList viewNames = QSqlDatabase::database(folderItem->connectionName()).tables(QSql::Views);
  foreach (QString name, viewNames){
    DBViewItem* viewItem = newViewItem(name, folderItem);
    viewItem->setParentUrl(folderItem->objectUrl());
  }
}
