#include "mysqlfolderitem.h"
#include "sdk/utils/qsqlqueryhelper.h"
#include "sdk/objects/appconst.h"
#include "sdk/objects/dbtriggeritem.h"
#include "sdk/objects/dbprocedureitem.h"
#include "sdk/objects/dbsequenceitem.h"
#include "sdk/core/iocplugin.h"
#include "sdk/core/core.h"


MysqlFolderItem::MysqlFolderItem() : FolderTreeItem()
{
}


void MysqlFolderItem::loadChildren()
{
    switch (childrenType()) {
    case DBObjectItem::Table:
    case DBObjectItem::SystemTable:
    case DBObjectItem::View:
        FolderTreeItem::loadChildren();
        return;
    default:
        QString sql;

        QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
        while (resultSet.next()){
            DBObjectItem* childItem = nullptr;
            switch (childrenType()) {
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

}
