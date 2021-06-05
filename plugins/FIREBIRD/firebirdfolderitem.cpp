#include "firebirdfolderitem.h"
#include "qsqlqueryhelper.h"
#include "core/basepluginmanager.h"
#include "sdk/objects/dbprocedureitem.h"
#include "sdk/objects/dbtriggeritem.h"
#include "sdk/objects/dbsequenceitem.h"
#include "sdk/objects/appconst.h"


FirebirdFolderItem::FirebirdFolderItem(QObject *parent) : FolderTreeItem(parent)
{
}


void FirebirdFolderItem::loadChildren()
{
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
            childItem = qobject_cast<DBSequenceItem*>(
                        BasePluginManager::instance()->newDbmsObject(driverName(),
                                                               DBObjectItem::Sequence,
                                                               resultSet.value(F_NAME).toString(),
                                                               this));
            break;
        case DBObjectItem::Procedure:
            childItem = qobject_cast<DBProcedureItem*>(
                        BasePluginManager::instance()->newDbmsObject(driverName(),
                                                               DBObjectItem::Procedure,
                                                               resultSet.value(F_NAME).toString(),
                                                               this));
            break;
        case DBObjectItem::Trigger:
            childItem = qobject_cast<DBTriggerItem*>(
                        BasePluginManager::instance()->newDbmsObject(driverName(),
                                                               DBObjectItem::Trigger,
                                                               resultSet.value(F_NAME).toString(),
                                                               this));
            break;
        default:
            break;
        }
        if (childItem)
            childItem->setParentUrl(objectUrl());
    }
}
