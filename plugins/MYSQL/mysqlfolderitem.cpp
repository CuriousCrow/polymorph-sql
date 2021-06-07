#include "mysqlfolderitem.h"
#include "qsqlqueryhelper.h"
#include "sdk/objects/appconst.h"
#include "sdk/objects/dbtriggeritem.h"
#include "sdk/objects/dbprocedureitem.h"
#include "sdk/objects/dbsequenceitem.h"
#include "core/basepluginmanager.h"
#include "sdk/core/iocplugin.h"
#include "core/core.h"


MysqlFolderItem::MysqlFolderItem() : FolderTreeItem()
{
}


void MysqlFolderItem::loadChildren()
{
    IocPlugin* plugin = Core::plugin(driverName(), FeatureType::DbmsObjects);
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
                childItem = plugin->dependency<DBSequenceItem>(QVariantHash());
                break;
            case DBObjectItem::Procedure:
                childItem = plugin->dependency<DBProcedureItem>(QVariantHash());
                break;
            case DBObjectItem::Trigger:
                childItem = plugin->dependency<DBTriggerItem>(QVariantHash());
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
