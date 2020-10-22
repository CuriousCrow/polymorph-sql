#include "postgresdatabase.h"
#include "postgrestable.h"
#include "postgressequence.h"
#include "../appconst.h"
#include "postgresfunctionitem.h"
#include "postgrestriggeritem.h"


PostgresDatabase::PostgresDatabase(QString caption) : DBDatabaseItem(caption)
{
  setFieldValue(F_DRIVER_NAME, DRIVER_POSTGRES);
}

PostgresDatabase::~PostgresDatabase()
{
}

QString PostgresDatabase::getViewListSql()
{
  return "select table_name \"name\", view_definition \"queryText\" "
         "from INFORMATION_SCHEMA.views where table_schema = 'public'";
}

QString PostgresDatabase::getSequenceListSql()
{
  return "SELECT sequence_name \"name\", start_value \"startValue\", minimum_value \"minValue\", maximum_value \"maxValue\", increment \"step\" "
         "FROM information_schema.sequences order by 1";
}

QString PostgresDatabase::getTriggerListSql()
{
  return "SELECT distinct(trigger_name) \"name\" "
         "FROM information_schema.triggers order by 1";
}

QString PostgresDatabase::getProcedureListSql()
{
  return "SELECT distinct(routine_name) \"name\" FROM information_schema.routines "
      "WHERE routine_type='FUNCTION' and specific_schema='public' order by 1";
}

DBTableItem *PostgresDatabase::createNewTableItem(QString caption, QObject *parent)
{
  return new PostgresTable(caption, parent);
}

DBSequenceItem *PostgresDatabase::createNewSequenceItem(QString caption, QObject *parent)
{
  return new PostgresSequence(caption, parent);
}

void PostgresDatabase::loadSequenceItems(DBObjectItem *parentItem)
{
  QString sql = getSequenceListSql();
  QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
  while (resultSet.next()) {
    DBSequenceItem* sequenceItem = createNewSequenceItem(resultSet.value(F_NAME).toString(), parentItem);
    sequenceItem->setParentUrl(parentItem->objectUrl());
  }
}

void PostgresDatabase::loadTriggerItems(DBObjectItem *parentItem)
{
  DBDatabaseItem::loadTriggerItems(parentItem);
}

void PostgresDatabase::loadProcedureItems(DBObjectItem *parentItem)
{
  DBDatabaseItem::loadProcedureItems(parentItem);
}


DBProcedureItem *PostgresDatabase::createNewProcedureItem(QString caption, QObject *parent)
{
  return new PostgresFunctionItem(caption, parent);
}

DBTriggerItem *PostgresDatabase::createNewTriggerItem(QString caption, QObject *parent)
{
  return new PostgresTriggerItem(caption, parent);
}

QString PostgresDatabase::getAllObjectListSql()
{
  return "select table_name \"name\", 'table' \"type\" FROM information_schema.tables "
         "WHERE table_schema = 'public' AND table_type = 'BASE TABLE' "
         "UNION ALL "
         "SELECT table_name, 'view' FROM information_schema.views "
         "WHERE table_schema = 'public' "
         "UNION ALL "
         "SELECT sequence_name, 'sequence' FROM information_schema.sequences "
         "UNION ALL "
         "SELECT routine_name, 'procedure' FROM information_schema.routines "
         "WHERE specific_schema NOT IN ('pg_catalog', 'information_schema') "
         "AND type_udt_name != 'trigger'";
}
