#include "sqlitedatabase.h"
#include "objects/foldertreeitem.h"
#include "objects/dbtableitem.h"
#include "objects/appconst.h"
#include "sqlitetable.h"


SqliteDatabase::SqliteDatabase()
  : DBDatabaseItem("")
{
  setFieldValue(F_DRIVER_NAME, DRIVER_SQLITE);
  setFieldValue(F_PORT, QVariant());
}

ActionResult SqliteDatabase::insertMe()
{
  QString sql = "insert into t_database (NAME, DRIVER, LOCAL_PATH, HOST_ADDRESS, USERNAME, PASSWORD) "
                "values ('#caption#','#driverName#', '#databaseName#', '#hostName#', '#userName#', '#password#')";
  QSqlQuery sqlResult = QSqlQueryHelper::execSql(fillSqlPatternWithFields(sql));
  if (sqlResult.lastError().isValid()){
    return ActionResult(ERR_QUERY_ERROR, sqlResult.lastError().databaseText());
  }
  else {
    setFieldValue("id", sqlResult.lastInsertId());
    return RES_OK_CODE;
  }
}

bool SqliteDatabase::reloadChildren()
{
  return true;
}

QString SqliteDatabase::getAllObjectListSql() const
{
  return "SELECT name, type FROM sqlite_master";
}
