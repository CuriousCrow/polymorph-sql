#include "firebirddatabase.h"
#include "firebirdtable.h"
#include "sdk/objects/appconst.h"

FirebirdDatabase::FirebirdDatabase()
  : DBDatabaseItem("")
{
  setFieldValue(F_DRIVER_NAME, DRIVER_FIREBIRD);
}

QString FirebirdDatabase::getAllObjectListSql() const
{
  return "select trim(rdb$relation_name), 'table' from rdb$relations where rdb$relation_type=0 and (rdb$system_flag is null or rdb$system_flag = 0) "
         "union all "
         "select trim(rdb$relation_name) name, 'view' from rdb$relations where rdb$relation_type=1 "
         "union all "
         "select trim(rdb$generator_name) name, 'sequence' from rdb$generators where rdb$system_flag = 0 "
         "union all "
         "select trim(rdb$procedure_name) name, 'procedure' from rdb$procedures";
}
