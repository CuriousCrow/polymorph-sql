#include "qdbpostgresitem.h"
#include "qdbpostgrestableitem.h"
#include "qdbpostgresequence.h"
#include "../appconst.h"


QDBPostgresItem::QDBPostgresItem(QString caption, QObject *parent) : QDBDatabaseItem(caption, parent)
{

}

QDBPostgresItem::~QDBPostgresItem()
{
}

QString QDBPostgresItem::getViewListSql()
{
  return "select table_name \"name\", view_definition \"queryText\" from INFORMATION_SCHEMA.views where table_schema = 'public'";
}

QString QDBPostgresItem::getSequenceListSql()
{
  return "SELECT sequence_name \"name\", start_value \"startValue\", minimum_value \"minValue\", maximum_value \"maxValue\", increment \"step\" FROM information_schema.sequences";
}

QString QDBPostgresItem::getTriggerListSql()
{
  return "SELECT distinct(trigger_name) \"name\" FROM information_schema.triggers order by 1";
}

QString QDBPostgresItem::getProcedureListSql()
{
  return "SELECT distinct(routine_name) \"name\" FROM information_schema.routines "
      "WHERE routine_type='FUNCTION' and specific_schema='public' order by 1";
}

QDBTableItem *QDBPostgresItem::createNewTableItem(QString caption, QObject *parent)
{
  return new QDBPostgresTableItem(caption, parent);
}

QDBSequenceItem *QDBPostgresItem::createNewSequenceItem(QString caption, QObject *parent)
{
  return new QDBPostgreSequence(caption, parent);
}

void QDBPostgresItem::loadViewItems(QDBObjectItem *parentItem)
{
  QDBDatabaseItem::loadViewItems(parentItem);
}

void QDBPostgresItem::loadSequenceItems(QDBObjectItem *parentItem)
{
  QString sql = getSequenceListSql();
  QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
  while (resultSet.next()) {
    QDBSequenceItem* sequenceItem
        = createNewSequenceItem(resultSet.value(F_NAME).toString(), parentItem);
    sequenceItem->updateObjectName();
  }
}

void QDBPostgresItem::loadTriggerItems(QDBObjectItem *parentItem)
{
  QDBDatabaseItem::loadTriggerItems(parentItem);
}

void QDBPostgresItem::loadProcedureItems(QDBObjectItem *parentItem)
{
  QDBDatabaseItem::loadProcedureItems(parentItem);
}
