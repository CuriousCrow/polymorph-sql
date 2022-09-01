#include "firebirddatabase.h"
#include "firebirdtable.h"
#include "objects/appconst.h"

#define FIREBIRD_PORT 3060

FirebirdDatabase::FirebirdDatabase()
  : DBDatabaseItem("")
{
  setFieldValue(F_DRIVER_NAME, DRIVER_FIREBIRD);
  setFieldValue(F_PORT, FIREBIRD_PORT);
}

QString FirebirdDatabase::getAllObjectListSql() const
{
  return "select trim(rdb$relation_name) as \"name\", trim('table') as \"type\" from rdb$relations where rdb$relation_type=0 and (rdb$system_flag is null or rdb$system_flag = 0) "
         "union all "
         "select trim(rdb$relation_name) name, trim('view') from rdb$relations where rdb$relation_type=1 "
         "union all "
         "select trim(rdb$generator_name) name, trim('sequence') from rdb$generators where rdb$system_flag = 0 "
         "union all "
         "select trim(rdb$procedure_name) name, trim('procedure') from rdb$procedures";
}
