#include "sqlitedatabase.h"
#include "../foldertreeitem.h"
#include "../dbtableitem.h"
#include "../appconst.h"
#include "sqlitetable.h"



SqliteDatabase::SqliteDatabase(QString caption)
  : DBDatabaseItem(caption)
{
  setFieldValue(F_DRIVER_NAME, DRIVER_SQLITE);
}


bool SqliteDatabase::reloadChildren()
{
  if (!children().isEmpty())
    return false;

  //Creating table items
  FolderTreeItem* tableFolderItem = new FolderTreeItem(FOLDER_TABLES, tr("Tables"), this);
  tableFolderItem->setChildrenType(Table);
  QStringList tableNames = QSqlDatabase::database(connectionName()).tables();
  foreach (QString name, tableNames){
    new SqliteTableItem(name, tableFolderItem);
  }

  //Creating views items
  FolderTreeItem* viewFolderItem = new FolderTreeItem(FOLDER_VIEWS, tr("Views"), this);
  viewFolderItem->setChildrenType(View);
  loadViewItems(viewFolderItem);

  //Creating system table items
  FolderTreeItem* systemFolderItem = new FolderTreeItem(FOLDER_SYSTABLES, tr("System tables"), this);
  systemFolderItem->setChildrenType(Table);
  QStringList sysTableNames = QSqlDatabase::database(connectionName()).tables(QSql::SystemTables);
  foreach (QString name, sysTableNames){
    new SqliteTableItem(name, systemFolderItem);
  }

  //Creating sequence items
  FolderTreeItem* sequenceFolderItem = new FolderTreeItem(FOLDER_SEQUENCES, tr("Generators"), this);
  sequenceFolderItem->setChildrenType(Sequence);
  loadSequenceItems(sequenceFolderItem);

  //Creating trigger items
  FolderTreeItem* triggerFolderItem = new FolderTreeItem(FOLDER_TRIGGERS, tr("Triggers"), this);
  triggerFolderItem->setChildrenType(Trigger);
  loadTriggerItems(triggerFolderItem);

  return true;
}

DBTableItem *SqliteDatabase::createNewTableItem(QString caption, QObject *parent)
{
  return new SqliteTableItem(caption, parent);
}

QString SqliteDatabase::getViewListSql()
{
  return "select trim(name) name, sql queryText from sqlite_master where type='view'";
}

QString SqliteDatabase::getSequenceListSql()
{
  return "";
}

QString SqliteDatabase::getTriggerListSql()
{
  return "select name name from sqlite_master where type = 'trigger'";
}

QString SqliteDatabase::getProcedureListSql()
{
  return "";
}

void SqliteDatabase::loadSequenceItems(DBObjectItem *parentItem)
{
  QString sql = "SELECT name, seq currentValue FROM sqlite_sequence";
  QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
  while (resultSet.next()) {
    DBSequenceItem* sequenceItem
        = createNewSequenceItem(resultSet.value(F_NAME).toString(), parentItem);
    sequenceItem->setFieldValue(F_CURRENT_VALUE, resultSet.value(F_CURRENT_VALUE).toInt());
    sequenceItem->setParentUrl(parentItem->objectUrl());
  }
}
