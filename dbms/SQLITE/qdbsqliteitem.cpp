#include "qdbsqliteitem.h"
#include "../qfoldertreeitem.h"
#include "../qdbtableitem.h"
#include "../appconst.h"
#include "qdbsqlitetableitem.h"



DBSqliteItem::DBSqliteItem(QString caption)
  : DBDatabaseItem(caption)
{
  setFieldValue(F_DRIVER_NAME, DRIVER_SQLITE);
}


bool DBSqliteItem::reloadChildren()
{
  if (!children().isEmpty())
    return false;

  //Creating table items
  FolderTreeItem* tableFolderItem = new FolderTreeItem(tr("Tables"), this);
  tableFolderItem->setChildrenType(Table);
  QStringList tableNames = QSqlDatabase::database(connectionName()).tables();
  foreach (QString name, tableNames){
    new DBSqliteTableItem(name, tableFolderItem);
  }

  //Creating views items
  FolderTreeItem* viewFolderItem = new FolderTreeItem(tr("Views"), this);
  viewFolderItem->setChildrenType(View);
  loadViewItems(viewFolderItem);

  //Creating system table items
  FolderTreeItem* systemFolderItem = new FolderTreeItem(tr("System tables"), this);
  systemFolderItem->setChildrenType(Table);
  QStringList sysTableNames = QSqlDatabase::database(connectionName()).tables(QSql::SystemTables);
  foreach (QString name, sysTableNames){
    new DBSqliteTableItem(name, systemFolderItem);
  }

  //Creating sequence items
  FolderTreeItem* sequenceFolderItem = new FolderTreeItem(tr("Generators"), this);
  sequenceFolderItem->setChildrenType(Sequence);
  loadSequenceItems(sequenceFolderItem);

  //Creating trigger items
  FolderTreeItem* triggerFolderItem = new FolderTreeItem(tr("Triggers"), this);
  triggerFolderItem->setChildrenType(Trigger);
  loadTriggerItems(triggerFolderItem);

  return true;
}

DBTableItem *DBSqliteItem::createNewTableItem(QString caption, QObject *parent)
{
  return new DBSqliteTableItem(caption, parent);
}

QString DBSqliteItem::getViewListSql()
{
  return "select trim(name) name, sql queryText from sqlite_master where type='view'";
}

QString DBSqliteItem::getSequenceListSql()
{
  return "";
}

QString DBSqliteItem::getTriggerListSql()
{
  return "select name name from sqlite_master where type = 'trigger'";
}

QString DBSqliteItem::getProcedureListSql()
{
  return "";
}

void DBSqliteItem::loadSequenceItems(DBObjectItem *parentItem)
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
