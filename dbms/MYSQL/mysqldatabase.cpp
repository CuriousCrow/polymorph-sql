#include "mysqldatabase.h"
#include "mysqltable.h"
#include "../foldertreeitem.h"
#include "../appconst.h"


MysqlDatabase::MysqlDatabase(QString caption)
  : DBDatabaseItem(caption)
{
  setFieldValue(F_DRIVER_NAME, DRIVER_MYSQL);
}

MysqlDatabase::~MysqlDatabase()
{
}

DBTableItem *MysqlDatabase::createNewTableItem(QString caption, QObject *parent)
{
  return new DBMysqlTableItem(caption, parent);
}

bool MysqlDatabase::reloadChildren()
{
  if (!children().isEmpty())
    return false;

  //Creating table items
  FolderTreeItem* tableFolderItem = new FolderTreeItem(FOLDER_TABLES, tr("Tables"), this);
  tableFolderItem->setChildrenType(Table);
  QStringList tableNames = QSqlDatabase::database(connectionName()).tables();
  foreach (QString name, tableNames){
    createNewTableItem(name, tableFolderItem);
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
    new DBMysqlTableItem(name, systemFolderItem);
  }

  //  //Creating trigger items
  //  FolderTreeItem* triggerFolderItem = new FolderTreeItem(tr("Triggers"), this);
  //  triggerFolderItem->setChildrenType(Trigger);
  //  loadTriggerItems(triggerFolderItem);

  return true;
}

QString MysqlDatabase::getViewListSql()
{
  return "select table_name \"name\" from INFORMATION_SCHEMA.views";
}

QString MysqlDatabase::getSequenceListSql()
{
  return "";
}

QString MysqlDatabase::getTriggerListSql()
{
  return "";
}

QString MysqlDatabase::getProcedureListSql()
{
  return "";
}
