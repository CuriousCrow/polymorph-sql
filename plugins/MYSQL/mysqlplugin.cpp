#include "mysqlplugin.h"
#include "sdk/objects/appconst.h"
#include "mysqldatabase.h"
#include "mysqltable.h"
#include "sdk/objects/dbsequenceitem.h"
#include "sdk/objects/dbviewitem.h"
#include "sdk/objects/dbprocedureitem.h"
#include "sdk/objects/dbtriggeritem.h"



QString MysqlPlugin::driver()
{
  return DRIVER_MYSQL;
}

DBDatabaseItem *MysqlPlugin::newDatabaseItem(QString caption, QObject *parent)
{
  Q_UNUSED(parent)
  return new MysqlDatabase(caption);
}

DBTableItem *MysqlPlugin::newTableItem(QString caption, QObject *parent)
{
  return new MysqlTableItem(caption, parent);
}

DBViewItem *MysqlPlugin::newViewItem(QString caption, QObject *parent)
{
  return new DBViewItem(caption, parent);
}

DBProcedureItem *MysqlPlugin::newProcedureItem(QString caption, QObject *parent)
{
  return new DBProcedureItem(caption, parent);
}

DBSequenceItem *MysqlPlugin::newSequenceItem(QString caption, QObject *parent)
{
  return new DBSequenceItem(caption, parent);
}

DBTriggerItem *MysqlPlugin::newTriggerItem(QString caption, QObject *parent)
{
    return new DBTriggerItem(caption, parent);
}

FolderTreeItem *MysqlPlugin::newFolderItem(QObject *parent)
{
    return new FolderTreeItem(parent);
}

AbstractDatabaseEditForm *MysqlPlugin::formByType(DBObjectItem::ItemType type)
{
  Q_UNUSED(type)
  return nullptr;
}


FolderTreeItem *MysqlPlugin::loadFolder(FolderTreeItem *folderItem, DBObjectItem::ItemType childrenType)
{
  QString sql;
  switch (childrenType) {
  case DBObjectItem::Table:
    break;
  case DBObjectItem::View:
    sql = "select table_name \"name\" from INFORMATION_SCHEMA.views";
    break;
//  case DBObjectItem::Sequence:
//    sql = "";
//    break;
//  case DBObjectItem::Procedure:
//    sql = "";
//    break;
//  case DBObjectItem::Trigger:
//    sql = "";
//    break;
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

QList<DBObjectItem::ItemType> MysqlPlugin::supportedTypes()
{
  QList<DBObjectItem::ItemType> types;
  types.append(DBObjectItem::Table);
  types.append(DBObjectItem::View);
  types.append(DBObjectItem::Sequence);
  types.append(DBObjectItem::Procedure);
  types.append(DBObjectItem::Trigger);
  return types;
}

QString MysqlPlugin::folderName(DBObjectItem::ItemType type)
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
