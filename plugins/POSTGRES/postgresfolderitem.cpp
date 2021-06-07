#include "postgresfolderitem.h"
#include "postgresdatabase.h"
#include "sdk/objects/appconst.h"
#include "core/core.h"
#include "sdk/core/iocplugin.h"
#include "qsqlqueryhelper.h"

PostgresFolderItem::PostgresFolderItem() : FolderTreeItem()
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
    IocPlugin* plugin = Core::plugin(driverName(), FeatureType::DbmsObjects);
    qDebug() << DRIVER_POSTGRES << "loading sequences";
    QString sql = "select sequence_name \"name\" from information_schema.sequences";
    QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
    while (resultSet.next()) {
      DBSequenceItem* sequenceItem = plugin->dependency<DBSequenceItem>(QVariantHash());
      sequenceItem->setParent(this);
      sequenceItem->setFieldValue(F_CAPTION, resultSet.value(F_NAME));
      sequenceItem->setParentUrl(objectUrl());
    }
}

void PostgresFolderItem::loadTriggers()
{
    IocPlugin* plugin = Core::plugin(driverName(), FeatureType::DbmsObjects);
    qDebug() << DRIVER_POSTGRES << "loading triggers";
    QString sql = "SELECT distinct(trigger_name) \"name\" "
                  "FROM information_schema.triggers order by 1";
    QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
    while (resultSet.next()) {
      DBTriggerItem* triggerItem = plugin->dependency<DBTriggerItem>(QVariantHash());
      triggerItem->setParent(this);
      triggerItem->setFieldValue(F_CAPTION, resultSet.value(F_NAME));
      triggerItem->setParentUrl(objectUrl());
    }
}

void PostgresFolderItem::loadProcedures()
{
    IocPlugin* plugin = Core::plugin(driverName(), FeatureType::DbmsObjects);
    qDebug() << DRIVER_POSTGRES << "loading procedures";
    QString sql = "SELECT distinct(routine_name) \"name\" FROM information_schema.routines "
                  "WHERE routine_type='FUNCTION' and specific_schema='public' order by 1";
    QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
    while (resultSet.next()) {
      DBProcedureItem* procedureItem = plugin->dependency<DBProcedureItem>(QVariantHash());
      procedureItem->setParent(this);
      procedureItem->setFieldValue(F_CAPTION, resultSet.value(F_NAME));
      procedureItem->setParentUrl(objectUrl());
    }
}
