#include "mysqluniqueconstraint.h"
#include "objects/appconst.h"
#include "utils/sqlqueryhelper.h"

MysqlUniqueConstraint::MysqlUniqueConstraint() : DBUniqueConstraint("", Q_NULLPTR)
{
  _identifierSupport = new BacktickIdentifier();
}


bool MysqlUniqueConstraint::refresh()
{
  QString sql =
      "select cu.COLUMN_NAME \"column\" "
      "from INFORMATION_SCHEMA.KEY_COLUMN_USAGE cu "
      "where cu.TABLE_SCHEMA = '#databaseName#' "
      "and CONSTRAINT_NAME = '#caption#' and cu.TABLE_NAME = '#table#'";
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
