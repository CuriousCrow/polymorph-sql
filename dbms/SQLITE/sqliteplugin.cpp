#include "sqliteplugin.h"
#include "../appconst.h"
#include "sqlitedatabase.h"
#include "sqlitetable.h"
#include "sqliteviewitem.h"
#include "../dbsequenceitem.h"

SqlitePlugin::SqlitePlugin() : DbmsPlugin()
{
}

QString SqlitePlugin::driver()
{
  return DRIVER_SQLITE;
}

DBDatabaseItem *SqlitePlugin::newDatabaseItem(QString caption, QObject *parent)
{
  Q_UNUSED(parent)
  return new SqliteDatabase(caption);
}

DBTableItem *SqlitePlugin::newTableItem(QString caption, QObject *parent)
{
  return new SqliteTableItem(caption, parent);
}

DBViewItem *SqlitePlugin::newViewItem(QString caption, QObject *parent)
{
  Q_UNUSED(caption)
  Q_UNUSED(parent)
  return new SqliteViewItem(caption, parent);
}

DBProcedureItem *SqlitePlugin::newProcedureItem(QString caption, QObject *parent)
{
  Q_UNUSED(caption)
  Q_UNUSED(parent)
  return nullptr;
}

DBSequenceItem *SqlitePlugin::newSequenceItem(QString caption, QObject *parent)
{
  Q_UNUSED(caption)
  Q_UNUSED(parent)
  return new DBSequenceItem(caption, parent);
}

DBTriggerItem *SqlitePlugin::newTriggerItem(QString caption, QObject *parent)
{
  Q_UNUSED(caption)
  Q_UNUSED(parent)
  return nullptr;
}

AbstractDatabaseEditForm *SqlitePlugin::formByType(DBObjectItem::ItemType type)
{
  Q_UNUSED(type)
  return nullptr;
}

FolderTreeItem *SqlitePlugin::loadFolder(FolderTreeItem *folderItem, DBObjectItem::ItemType childrenType)
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
  case DBObjectItem::SystemTable:
    loadSysTables(folderItem);
    break;
  default:
    folderItem = nullptr;
    break;
  }
  return folderItem;
}

void SqlitePlugin::loadSequences(FolderTreeItem *folderItem)
{
  QString sql = "SELECT name, seq currentValue FROM sqlite_sequence";
  QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, folderItem->connectionName());
  while (resultSet.next()) {
    DBSequenceItem* sequenceItem
        = newSequenceItem(resultSet.value(F_NAME).toString(), folderItem);
    sequenceItem->setFieldValue(F_CURRENT_VALUE, resultSet.value(F_CURRENT_VALUE).toInt());
    sequenceItem->setParentUrl(folderItem->objectUrl());
  }
}

void SqlitePlugin::loadTables(FolderTreeItem *folderItem)
{
  QStringList tableNames = QSqlDatabase::database(folderItem->connectionName()).tables();
  foreach (QString name, tableNames){
    DBTableItem* tableItem = newTableItem(name, folderItem);
    tableItem->setParentUrl(folderItem->objectUrl());
  }
}

void SqlitePlugin::loadSysTables(FolderTreeItem *folderItem)
{
  QStringList tableNames = QSqlDatabase::database(folderItem->connectionName()).tables(QSql::SystemTables);
  foreach (QString name, tableNames){
    DBTableItem* tableItem = newTableItem(name, folderItem);
    tableItem->setParentUrl(folderItem->objectUrl());
  }
}

void SqlitePlugin::loadViews(FolderTreeItem *folderItem)
{
  QStringList viewNames = QSqlDatabase::database(folderItem->connectionName()).tables(QSql::Views);
  foreach (QString name, viewNames){
    DBViewItem* viewItem = newViewItem(name, folderItem);
    viewItem->setParentUrl(folderItem->objectUrl());
  }
}

void SqlitePlugin::loadTriggers(FolderTreeItem *folderItem)
{
  QString sql = "select name name from sqlite_master where type = 'trigger'";
  QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, folderItem->connectionName());
  while (resultSet.next()) {
    DBSequenceItem* sequenceItem
        = newSequenceItem(resultSet.value(F_NAME).toString(), folderItem);
    sequenceItem->setFieldValue(F_CURRENT_VALUE, resultSet.value(F_CURRENT_VALUE).toInt());
    sequenceItem->setParentUrl(folderItem->objectUrl());
  }
}

void SqlitePlugin::loadProcedures(FolderTreeItem *folderItem)
{
  Q_UNUSED(folderItem)
}

QList<DBObjectItem::ItemType> SqlitePlugin::supportedTypes()
{
  QList<DBObjectItem::ItemType> types;
  types.append(DBObjectItem::Table);
  types.append(DBObjectItem::View);
  types.append(DBObjectItem::SystemTable);
  types.append(DBObjectItem::Sequence);
  return types;
}

QString SqlitePlugin::folderName(DBObjectItem::ItemType type)
{
  switch (type) {
  case DBObjectItem::Table:
    return "Tables";
  case DBObjectItem::SystemTable:
    return "System tables";
  case DBObjectItem::View:
    return "Views";
  case DBObjectItem::Sequence:
    return "Sequence";
  default:
    return "";
  }
}
