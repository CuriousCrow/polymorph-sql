#include "firebirdfolderitem.h"
#include "qsqlqueryhelper.h"
#include "core/basepluginmanager.h"
#include "core/core.h"
#include "sdk/objects/dbprocedureitem.h"
#include "sdk/objects/dbtriggeritem.h"
#include "sdk/objects/dbsequenceitem.h"
#include "sdk/objects/appconst.h"


FirebirdFolderItem::FirebirdFolderItem() : FolderTreeItem()
{
}


void FirebirdFolderItem::loadChildren()
{
    IocPlugin* plugin = Core::plugin(driverName(), FeatureType::DbmsObjects);
    QString sql;
    switch (childrenType()) {
    case DBObjectItem::Table:
    case DBObjectItem::View:
    case DBObjectItem::SystemTable:
        FolderTreeItem::loadChildren();
        return;
    case DBObjectItem::Sequence:
        sql = "select rdb$generator_id id, trim(rdb$generator_name) name from rdb$generators where rdb$system_flag = 0";
        break;
    case DBObjectItem::Procedure:
        sql = "select rdb$procedure_id id, trim(rdb$procedure_name) name from rdb$procedures";
        break;
    case DBObjectItem::Trigger:
        sql = "select trim(rdb$trigger_name) name from rdb$triggers where rdb$system_flag = 0";
        break;
    default:
        return;
    }

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
