#include "firebirdplugin.h"
#include "sdk/objects/appconst.h"
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

FolderTreeItem *FirebirdPlugin::newFolderItem(DBObjectItem::ItemType type, QObject *parent)
{
    FolderTreeItem* folder = new FolderTreeItem(parent);
    folder->setChildrenType(type);
    return folder;
}

AbstractDatabaseEditForm *FirebirdPlugin::formByType(DBObjectItem::ItemType type)
{
  Q_UNUSED(type)
  return nullptr;
}


FolderTreeItem *FirebirdPlugin::loadFolder(FolderTreeItem *folderItem, DBObjectItem::ItemType childrenType)
{
  QString sql;
  switch (childrenType) {
  case DBObjectItem::Table:
    loadTables(folderItem);
    return folderItem;
  case DBObjectItem::View:
//    sql = "select trim(rdb$relation_name) name, rdb$view_source queryText from rdb$relations "
//          "where rdb$relation_type=1";
    loadViews(folderItem);
    return folderItem;
  case DBObjectItem::Sequence:
    sql = "select rdb$generator_id id, trim(rdb$generator_name) name from rdb$generators where rdb$system_flag = 0";
    break;
  case DBObjectItem::Procedure:
    sql = "select rdb$procedure_id id, trim(rdb$procedure_name) name from rdb$procedures";
    break;
  case DBObjectItem::Trigger:
    sql = "select trim(rdb$trigger_name) name from rdb$triggers where rdb$system_flag = 0";
    break;
  default:
    return folderItem;
  }

  QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, folderItem->connectionName());
  while (resultSet.next()){
    DBObjectItem* childItem = nullptr;
    switch (childrenType) {
    case DBObjectItem::Table:
      childItem = newTableItem(resultSet.value(F_NAME).toString(), folderItem);
      break;
    case DBObjectItem::View:
      childItem = newViewItem(resultSet.value(F_NAME).toString(), folderItem);
      break;
    case DBObjectItem::Sequence:
      childItem = newSequenceItem(resultSet.value(F_NAME).toString(), folderItem);
      break;
    case DBObjectItem::Procedure:
      childItem = newProcedureItem(resultSet.value(F_NAME).toString(), folderItem);
      break;
    case DBObjectItem::Trigger:
      childItem = newTriggerItem(resultSet.value(F_NAME).toString(), folderItem);
      break;
    default:
      break;
    }
    childItem->setParentUrl(folderItem->objectUrl());
  }
  return folderItem;
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
