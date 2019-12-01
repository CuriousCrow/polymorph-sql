#include "qdbpostgresitem.h"
#include "qdbpostgrestableitem.h"
#include "qdbpostgresequence.h"
#include "../appconst.h"
#include "qdbpostgreqfunctionitem.h"
#include "postgrestriggeritem.h"


DBPostgresItem::DBPostgresItem(QString caption) : DBDatabaseItem(caption)
{
  setFieldValue(F_DRIVER_NAME, DRIVER_POSTGRES);
}

DBPostgresItem::~DBPostgresItem()
{
}

QString DBPostgresItem::getViewListSql()
{
  return "select table_name \"name\", view_definition \"queryText\" "
         "from INFORMATION_SCHEMA.views where table_schema = 'public'";
}

QString DBPostgresItem::getSequenceListSql()
{
  return "SELECT sequence_name \"name\", start_value \"startValue\", minimum_value \"minValue\", maximum_value \"maxValue\", increment \"step\" "
         "FROM information_schema.sequences order by 1";
}

QString DBPostgresItem::getTriggerListSql()
{
  return "SELECT distinct(trigger_name) \"name\" "
         "FROM information_schema.triggers order by 1";
}

QString DBPostgresItem::getProcedureListSql()
{
  return "SELECT distinct(routine_name) \"name\" FROM information_schema.routines "
      "WHERE routine_type='FUNCTION' and specific_schema='public' order by 1";
}

DBTableItem *DBPostgresItem::createNewTableItem(QString caption, QObject *parent)
{
  return new DBPostgresTableItem(caption, parent);
}

DBSequenceItem *DBPostgresItem::createNewSequenceItem(QString caption, QObject *parent)
{
  return new DBPostgreSequence(caption, parent);
}

void DBPostgresItem::loadSequenceItems(DBObjectItem *parentItem)
{
  QString sql = getSequenceListSql();
  QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
  while (resultSet.next()) {
    DBSequenceItem* sequenceItem = createNewSequenceItem(resultSet.value(F_NAME).toString(), parentItem);
    sequenceItem->setParentUrl(parentItem->objectUrl());
  }
}

void DBPostgresItem::loadTriggerItems(DBObjectItem *parentItem)
{
  DBDatabaseItem::loadTriggerItems(parentItem);
}

void DBPostgresItem::loadProcedureItems(DBObjectItem *parentItem)
{
  DBDatabaseItem::loadProcedureItems(parentItem);
}


DBProcedureItem *DBPostgresItem::createNewProcedureItem(QString caption, QObject *parent)
{
  return new DBPostgreqFunctionItem(caption, parent);
}

DBTriggerItem *DBPostgresItem::createNewTriggerItem(QString caption, QObject *parent)
{
  return new PostgresTriggerItem(caption, parent);
}
