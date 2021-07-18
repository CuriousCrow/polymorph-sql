#include "postgresdatabase.h"
#include "postgrestable.h"
#include "postgressequence.h"
#include "objects/appconst.h"
#include "postgresfunctionitem.h"
#include "postgrestriggeritem.h"

#define POSTGRES_PORT 5432

PostgresDatabase::PostgresDatabase() : DBDatabaseItem("")
{
  setFieldValue(F_DRIVER_NAME, DRIVER_POSTGRES);
  setFieldValue(F_PORT, POSTGRES_PORT);
}

PostgresDatabase::~PostgresDatabase()
{
}

QString PostgresDatabase::getViewListSql() const
{
  return "select table_name \"name\", view_definition \"queryText\" "
         "from INFORMATION_SCHEMA.views where table_schema = 'public'";
}

QString PostgresDatabase::getSequenceListSql() const
{
  return "SELECT sequence_name \"name\", start_value \"startValue\", minimum_value \"minValue\", maximum_value \"maxValue\", increment \"step\" "
         "FROM information_schema.sequences order by 1";
}

QString PostgresDatabase::getTriggerListSql() const
{
  return "SELECT distinct(trigger_name) \"name\" "
         "FROM information_schema.triggers order by 1";
}

QString PostgresDatabase::getProcedureListSql() const
{
  return "SELECT distinct(routine_name) \"name\" FROM information_schema.routines "
      "WHERE routine_type='FUNCTION' and specific_schema='public' order by 1";
}

QString PostgresDatabase::getAllObjectListSql() const
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
