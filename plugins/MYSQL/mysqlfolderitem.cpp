#include "mysqlfolderitem.h"
#include "qsqlqueryhelper.h"
#include "sdk/objects/appconst.h"
#include "sdk/objects/dbtriggeritem.h"
#include "sdk/objects/dbprocedureitem.h"
#include "sdk/objects/dbsequenceitem.h"
#include "core/basepluginmanager.h"


MysqlFolderItem::MysqlFolderItem(QObject *parent) : FolderTreeItem(parent)
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

}
