#include "mysqlcheckconstraint.h"
#include "objects/appconst.h"
#include "utils/sqlqueryhelper.h"

MysqlCheckConstraint::MysqlCheckConstraint() : DBCheckConstraint("", Q_NULLPTR)
{
  _identifierSupport = new BacktickIdentifier();
}


bool MysqlCheckConstraint::refresh()
{
  QString sql =
      "select CONSTRAINT_NAME name, CHECK_CLAUSE expression "
      "from INFORMATION_SCHEMA.CHECK_CONSTRAINTS "
      "where CONSTRAINT_SCHEMA = '#databaseName#' AND CONSTRAINT_NAME = '#caption#'";
  QString preparedSql = fillSqlPatternWithFields(sql);
  QSqlQuery resultSet = SqlQueryHelper::execSql(preparedSql, connectionName());
  if (resultSet.next()) {
    setFieldValue(F_EXPRESSION, resultSet.value(F_EXPRESSION));
    submit();
    return true;
  }
  else {
    return false;
  }
}
