#include "sqlitedatabase.h"
#include "sdk/objects/foldertreeitem.h"
#include "sdk/objects/dbtableitem.h"
#include "sdk/objects/appconst.h"
#include "sqlitetable.h"


SqliteDatabase::SqliteDatabase()
  : DBDatabaseItem("")
{
  setFieldValue(F_DRIVER_NAME, DRIVER_SQLITE);
}

bool SqliteDatabase::reloadChildren()
{
  return true;
}

QString SqliteDatabase::getAllObjectListSql() const
{
  return "SELECT name, type FROM sqlite_master";
}
