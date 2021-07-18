#include "mysqlfolderitem.h"
#include "utils/qsqlqueryhelper.h"
#include "objects/appconst.h"
#include "objects/dbtriggeritem.h"
#include "objects/dbprocedureitem.h"
#include "objects/dbsequenceitem.h"
#include "objects/dbtableitem.h"
#include "objects/dbviewitem.h"
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
        sql = "";
        break;
    case DBObjectItem::View:
        sql = "select table_name name from information_schema.tables where table_schema = '#databaseName#' and table_type = 'VIEW'";
        break;
    default:
        sql = "";
    }
    sql = fillSqlPatternWithFields(sql);
    if (sql.isEmpty())
        return;

    QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
    while (resultSet.next()){
        DBObjectItem* childItem = nullptr;
        switch (childrenType()) {
        case DBObjectItem::Table:
            childItem = Core::instance()->dependencyForDriver<DBTableItem>(driverName());
            break;
        case DBObjectItem::View:
            childItem = Core::instance()->dependencyForDriver<DBViewItem>(driverName());
            break;
        case DBObjectItem::Sequence:
            childItem = Core::instance()->dependencyForDriver<DBSequenceItem>(driverName());
            break;
        case DBObjectItem::Procedure:
            childItem = Core::instance()->dependencyForDriver<DBProcedureItem>(driverName());
            break;
        case DBObjectItem::Trigger:
            childItem = Core::instance()->dependencyForDriver<DBTriggerItem>(driverName());
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
