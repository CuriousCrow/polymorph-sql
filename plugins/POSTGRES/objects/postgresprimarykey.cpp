#include "postgresprimarykey.h"

#include "objects/appconst.h"
#include "utils/sqlqueryhelper.h"

PostgresPrimaryKey::PostgresPrimaryKey()
  : DBPrimaryKey("", nullptr)
{

}

bool PostgresPrimaryKey::refresh()
{
  QString sql = "select column_name \"column\" from information_schema.constraint_column_usage\n"
      "where constraint_name='#caption#'";
  QString preparedSql = fillSqlPatternWithFields(sql);
  QSqlQuery resultSet = SqlQueryHelper::execSql(preparedSql, connectionName());
  QStringList columns;
  while (resultSet.next()) {
    columns.append(resultSet.value(F_COLUMN).toString());
  }
  //TODO: Check field column is not empty
  setFieldValue(F_COLUMN, columns.join(","));
  submit();
  return true;
}
