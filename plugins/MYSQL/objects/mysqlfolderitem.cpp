#include "mysqlfolderitem.h"

#include "core/iocplugin.h"
#include "core/core.h"
#include "objects/appconst.h"
#include "objects/dbtrigger.h"
#include "objects/dbprocedure.h"
#include "objects/dbsequence.h"
#include "objects/dbtableitem.h"
#include "objects/dbview.h"
#include "utils/sqlqueryhelper.h"


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
      setZeroStatsExpiry();
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
  tableNames << "ADMINISTRABLE_ROLE_AUTHORIZATIONS" << "APPLICABLE_ROLES" << "CHARACTER_SETS" <<
  "CHECK_CONSTRAINTS" << "COLLATION_CHARACTER_SET_APPLICABILITY" << "COLLATIONS" <<
  "COLUMN_PRIVILEGES" << "COLUMN_STATISTICS" << "COLUMNS" <<"COLUMNS_EXTENSIONS" <<
  "ENABLED_ROLES" << "ENGINES" << "EVENTS" <<"FILES" << "KEY_COLUMN_USAGE" <<
  "KEYWORDS" << "OPTIMIZER_TRACE" << "PARAMETERS" << "PARTITIONS" <<"PLUGINS" <<
  "PROCESSLIST" << "PROFILING" << "REFERENTIAL_CONSTRAINTS" << "RESOURCE_GROUPS" <<
  "ROLE_COLUMN_GRANTS" << "ROLE_ROUTINE_GRANTS" << "ROLE_TABLE_GRANTS" << "ROUTINES" <<
  "SCHEMA_PRIVILEGES" << "SCHEMATA" << "SCHEMATA_EXTENSIONS" << "ST_GEOMETRY_COLUMNS" <<
  "ST_SPATIAL_REFERENCE_SYSTEMS" << "ST_UNITS_OF_MEASURE" << "STATISTICS" << "TABLE_CONSTRAINTS" <<
  "TABLE_CONSTRAINTS_EXTENSIONS" << "TABLE_PRIVILEGES" << "TABLES" << "TABLES_EXTENSIONS" <<
  "TABLESPACES" << "TABLESPACES_EXTENSIONS" << "TRIGGERS" << "USER_ATTRIBUTES" <<
  "USER_PRIVILEGES" << "VIEW_ROUTINE_USAGE" << "VIEW_TABLE_USAGE" << "VIEWS";
  foreach(QString name, tableNames) {
    DBObjectItem* infoTable = _core->dependencyForDriver<DBTableItem>(driverName());
    infoTable->setFieldValue(F_CAPTION, "INFORMATION_SCHEMA." + name);
    infoTable->setParent(this);
    infoTable->setParentUrl(objectUrl());
  }
}

void MysqlFolderItem::setZeroStatsExpiry()
{
  QString sql = "SET SESSION information_schema_stats_expiry=0";
  ActionResult res = execSql(sql, connectionName());
  qDebug() << "Set zero stats expiry time:" << res.isSuccess() << res.description();
}
