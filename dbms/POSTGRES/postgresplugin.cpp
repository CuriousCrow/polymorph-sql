#include "postgresplugin.h"
#include "../appconst.h"
#include "postgresdatabase.h"
#include "postgrestable.h"
#include "postgressequence.h"
#include "postgrestriggeritem.h"
#include "postgresfunctionitem.h"
#include "../dbviewitem.h"


QString PostgresPlugin::driver()
{
  return DRIVER_PSQL;
}

DBDatabaseItem *PostgresPlugin::newDatabaseItem(QString caption, QObject *parent)
{
  Q_UNUSED(parent)
  return new PostgresDatabase(caption);
}

DBTableItem *PostgresPlugin::newTableItem(QString caption, QObject *parent)
{
  return new PostgresTable(caption, parent);
}

DBViewItem *PostgresPlugin::newViewItem(QString caption, QObject *parent)
{
  return new DBViewItem(caption, parent);
}

DBProcedureItem *PostgresPlugin::newProcedureItem(QString caption, QObject *parent)
{
  return new PostgresFunctionItem(caption, parent);
}

DBSequenceItem *PostgresPlugin::newSequenceItem(QString caption, QObject *parent)
{
  return new PostgresSequence(caption, parent);
}

DBTriggerItem *PostgresPlugin::newTriggerItem(QString caption, QObject *parent)
{
  return new PostgresTriggerItem(caption, parent);
}

AbstractDatabaseEditForm *PostgresPlugin::formByType(DBObjectItem::ItemType type)
{
  Q_UNUSED(type)
  return nullptr;
}

FolderTreeItem *PostgresPlugin::loadFolder(FolderTreeItem *folderItem, DBObjectItem::ItemType childrenType)
{
  switch (childrenType) {
  case DBObjectItem::Sequence:
    loadSequences(folderItem);
    break;
  case DBObjectItem::Table:
    loadTables(folderItem);
    break;
  case DBObjectItem::View:
    loadViews(folderItem);
    break;
  case DBObjectItem::Procedure:
    loadProcedures(folderItem);
    break;
  case DBObjectItem::Trigger:
    loadTriggers(folderItem);
    break;
  default:
    folderItem = nullptr;
    break;
  }
  return folderItem;
}

void PostgresPlugin::loadSequences(FolderTreeItem *folderItem)
{
  Q_UNUSED(folderItem)
}

void PostgresPlugin::loadTables(FolderTreeItem *folderItem)
{
  QStringList tableNames = QSqlDatabase::database(folderItem->connectionName()).tables();
  foreach (QString name, tableNames){
    DBTableItem* tableItem = newTableItem(name, folderItem);
    tableItem->setParentUrl(folderItem->objectUrl());
  }
}

void PostgresPlugin::loadViews(FolderTreeItem *folderItem)
{
  QStringList viewNames = QSqlDatabase::database(folderItem->connectionName()).tables(QSql::Views);
  foreach (QString name, viewNames){
    DBViewItem* viewItem = newViewItem(name, folderItem);
    viewItem->setParentUrl(folderItem->objectUrl());
  }
}

void PostgresPlugin::loadTriggers(FolderTreeItem *folderItem)
{
  QString sql = "SELECT distinct(trigger_name) \"name\" "
                "FROM information_schema.triggers order by 1";
  QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, folderItem->connectionName());
  while (resultSet.next()) {
    DBTriggerItem* triggerItem
        = newTriggerItem(resultSet.value(F_NAME).toString(), folderItem);
    triggerItem->setParentUrl(folderItem->objectUrl());
  }
}

void PostgresPlugin::loadProcedures(FolderTreeItem *folderItem)
{
  QString sql = "SELECT distinct(routine_name) \"name\" FROM information_schema.routines "
                "WHERE routine_type='FUNCTION' and specific_schema='public' order by 1";
  QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, folderItem->connectionName());
  while (resultSet.next()) {
    DBProcedureItem* procedureItem
        = newProcedureItem(resultSet.value(F_NAME).toString(), folderItem);
    procedureItem->setParentUrl(folderItem->objectUrl());
  }
}

QList<DBObjectItem::ItemType> PostgresPlugin::supportedTypes()
{
  QList<DBObjectItem::ItemType> types;
  types.append(DBObjectItem::Table);
  types.append(DBObjectItem::View);
  types.append(DBObjectItem::Sequence);
  types.append(DBObjectItem::Procedure);
  types.append(DBObjectItem::Trigger);
  return types;
}

QString PostgresPlugin::folderName(DBObjectItem::ItemType type)
{
  switch (type) {
  case DBObjectItem::Table:
    return "Tables";
  case DBObjectItem::SystemTable:
    return "System tables";
  case DBObjectItem::View:
    return "Views";
  case DBObjectItem::Sequence:
    return "Sequences";
  case DBObjectItem::Procedure:
    return "Procedures";
  case DBObjectItem::Trigger:
    return "Triggers";
  default:
    return "";
  }
}