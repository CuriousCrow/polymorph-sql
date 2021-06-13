#include "postgresfolderitem.h"
#include "postgresdatabase.h"
#include "sdk/objects/appconst.h"
#include "sdk/core/core.h"
#include "sdk/core/iocplugin.h"
#include "sdk/utils/qsqlqueryhelper.h"

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
    qDebug() << DRIVER_POSTGRES << "loading sequences";
    QString sql = "select sequence_name \"name\" from information_schema.sequences";
    QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
    while (resultSet.next()) {
      DBSequenceItem* sequenceItem = Core::instance()->dependencyForDriver<DBSequenceItem>(driverName());
      sequenceItem->setParent(this);
      sequenceItem->setFieldValue(F_CAPTION, resultSet.value(F_NAME));
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
      DBTriggerItem* triggerItem = Core::instance()->dependencyForDriver<DBTriggerItem>(driverName());
      triggerItem->setParent(this);
      triggerItem->setFieldValue(F_CAPTION, resultSet.value(F_NAME));
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
      DBProcedureItem* procedureItem = Core::instance()->dependencyForDriver<DBProcedureItem>(driverName());
      procedureItem->setParent(this);
      procedureItem->setFieldValue(F_CAPTION, resultSet.value(F_NAME));
      procedureItem->setParentUrl(objectUrl());
    }
}
