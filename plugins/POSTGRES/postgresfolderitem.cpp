#include "postgresfolderitem.h"
#include "postgresplugin.h"
#include "sdk/objects/appconst.h"
#include "core/basepluginmanager.h"

PostgresFolderItem::PostgresFolderItem(QObject *parent) : FolderTreeItem(parent)
{
}

void PostgresFolderItem::loadChildren()
{
    switch (childrenType()) {
    case DBObjectItem::Sequence:
      loadSequences();
      break;
    case DBObjectItem::Procedure:
      loadProcedures();
      break;
    case DBObjectItem::Trigger:
      loadTriggers();
      break;
    default:
      FolderTreeItem::loadChildren();
    }
}

void PostgresFolderItem::loadSequences()
{
    qDebug() << DRIVER_POSTGRES << "loading sequences";
    QString sql = "select sequence_name \"name\" from information_schema.sequences";
    QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
    while (resultSet.next()) {
      DBSequenceItem* sequenceItem = qobject_cast<DBSequenceItem*>(
                  BasePluginManager::instance()->newDbmsObject(driverName(),
                                                         DBObjectItem::Sequence,
                                                         resultSet.value(F_NAME).toString(),
                                                         this));
      sequenceItem->setParentUrl(objectUrl());
    }
}

void PostgresFolderItem::loadTriggers()
{
    qDebug() << DRIVER_POSTGRES << "loading triggers";
    QString sql = "SELECT distinct(trigger_name) \"name\" "
                  "FROM information_schema.triggers order by 1";
    QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
    while (resultSet.next()) {
      DBTriggerItem* triggerItem = qobject_cast<DBTriggerItem*>(
                  BasePluginManager::instance()->newDbmsObject(driverName(),
                                                         DBObjectItem::Trigger,
                                                         resultSet.value(F_NAME).toString(),
                                                         this));
      triggerItem->setParentUrl(objectUrl());
    }
}

void PostgresFolderItem::loadProcedures()
{
    qDebug() << DRIVER_POSTGRES << "loading procedures";
    QString sql = "SELECT distinct(routine_name) \"name\" FROM information_schema.routines "
                  "WHERE routine_type='FUNCTION' and specific_schema='public' order by 1";
    QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
    while (resultSet.next()) {
      DBProcedureItem* procedureItem = qobject_cast<DBProcedureItem*>(
                  BasePluginManager::instance()->newDbmsObject(driverName(),
                                                         DBObjectItem::Procedure,
                                                         resultSet.value(F_NAME).toString(),
                                                         this));
      procedureItem->setParentUrl(objectUrl());
    }
}
