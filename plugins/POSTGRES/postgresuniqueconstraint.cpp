#include "postgresuniqueconstraint.h"
#include "../../qsqlqueryhelper.h"
#include "sdk/objects/appconst.h"


PostgresUniqueConstraint::PostgresUniqueConstraint()
  : DBUniqueConstraint("", nullptr)
{

}


bool PostgresUniqueConstraint::refresh()
{
  QString sql = "select column_name \"column\" from information_schema.constraint_column_usage\n"
      "where constraint_name='#caption#'";
  QString preparedSql = fillSqlPattern(sql);
  QSqlQuery resultSet = QSqlQueryHelper::execSql(preparedSql, connectionName());
  QStringList columns;
  while (resultSet.next()) {
    columns.append(resultSet.value(F_COLUMN).toString());
  }
  //TODO: Check field column is not empty
  setFieldValue(F_COLUMN, columns.join(","));
  submit();
  return true;
}
