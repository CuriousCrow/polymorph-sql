#include "sqlitedatabase.h"
#include "../foldertreeitem.h"
#include "../dbtableitem.h"
#include "../appconst.h"
#include "sqlitetable.h"


SqliteDatabase::SqliteDatabase(QString caption)
  : DBDatabaseItem(caption)
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
