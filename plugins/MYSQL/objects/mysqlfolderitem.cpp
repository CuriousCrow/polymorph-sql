#include "mysqlfolderitem.h"
#include "utils/sqlqueryhelper.h"
#include "objects/appconst.h"
#include "objects/dbtrigger.h"
#include "objects/dbprocedure.h"
#include "objects/dbsequence.h"
#include "objects/dbtableitem.h"
#include "objects/dbview.h"
#include "core/iocplugin.h"
#include "core/core.h"


MysqlFolderItem::MysqlFolderItem() : FolderTreeItem()
{
}


void MysqlFolderItem::loadChildren()
{
    QString sql;

    switch (childrenType()) {
    case DBObjectItem::Table:
      sql = "select table_name name from information_schema.tables where table_schema = '#databaseName#' and table_type = 'BASE TABLE'";
      break;
    case DBObjectItem::SystemTable:
      loadInformationSchemaTables();
      return;
    case DBObjectItem::View:
      sql = "select table_name name from information_schema.tables where table_schema = '#databaseName#' and table_type = 'VIEW'";
      break;
    case DBObjectItem::Sequence:
      sql = "SELECT TABLE_NAME name FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = '#databaseName#' and AUTO_INCREMENT is not null";
      break;
    case DBObjectItem::Procedure:
      sql = "select ROUTINE_NAME name from INFORMATION_SCHEMA.ROUTINES where ROUTINE_SCHEMA = '#databaseName#'";
      break;
    case DBObjectItem::Trigger:
      sql = "select TRIGGER_NAME name from INFORMATION_SCHEMA.TRIGGERS where trigger_schema='#databaseName#'";
      break;
    default:
      sql = "";
    }
    sql = fillSqlPatternWithFields(sql);
    if (sql.isEmpty())
        return;

    QSqlQuery resultSet = SqlQueryHelper::execSql(sql, connectionName());
    while (resultSet.next()){
        DBObjectItem* childItem = nullptr;
        switch (childrenType()) {
        case DBObjectItem::Table:
            childItem = _core->dependencyForDriver<DBTableItem>(driverName());
            break;
        case DBObjectItem::View:
            childItem = _core->dependencyForDriver<DBViewItem>(driverName());
            break;
        case DBObjectItem::Sequence:
            childItem = _core->dependencyForDriver<DBSequenceItem>(driverName());
            break;
        case DBObjectItem::Procedure:
            childItem = _core->dependencyForDriver<DBProcedureItem>(driverName());
            break;
        case DBObjectItem::Trigger:
            childItem = _core->dependencyForDriver<DBTriggerItem>(driverName());
            break;
        default:
            break;
        }
        if (childItem) {
            childItem->setFieldValue(F_CAPTION, resultSet.value(F_NAME));
            childItem->setParent(this);
            childItem->setParentUrl(objectUrl());
        }
    }
}

QString MysqlFolderItem::folderName(ItemType type)
{
  if (type == DBObjectItem::Sequence) {
    return tr("Auto Increments");
  }
  return FolderTreeItem::folderName(type);
}

void MysqlFolderItem::loadInformationSchemaTables()
{
  QStringList tableNames;
  tableNames << "APPLICABLE_ROLES" << "CHARACTER_SETS" << "CHECK_CONSTRAINTS"
             << "COLLATIONS" << "COLUMN_PRIVELEGES" << "COLUMN_STATISTICS"
             << "COLUMNS" << "TABLES";
  foreach(QString name, tableNames) {
    DBObjectItem* infoTable = _core->dependencyForDriver<DBTableItem>(driverName());
    infoTable->setFieldValue(F_CAPTION, "INFORMATION_SCHEMA." + name);
    infoTable->setParent(this);
    infoTable->setParentUrl(objectUrl());
  }
}
