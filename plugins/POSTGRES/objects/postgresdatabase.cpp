#include "postgresdatabase.h"
#include "postgrestable.h"
#include "postgressequence.h"
#include "objects/appconst.h"
#include "postgresfunction.h"
#include "postgrestrigger.h"

#define POSTGRES_PORT 5432

PostgresDatabase::PostgresDatabase() : DBDatabaseItem("")
{
  setFieldValue(F_DRIVER_NAME, DRIVER_POSTGRES);
  setFieldValue(F_PORT, POSTGRES_PORT);
}

PostgresDatabase::~PostgresDatabase()
{
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
