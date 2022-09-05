#include "postgrescheckconstraint.h"
#include "utils/sqlqueryhelper.h"
#include "objects/appconst.h"


PostgresCheckConstraint::PostgresCheckConstraint()
  : DBCheckConstraint("", nullptr)
{
}

bool PostgresCheckConstraint::refresh()
{
  QString sql = "select check_clause \"expression\"\n"
      "from information_schema.check_constraints\n"
      "where constraint_name='#caption#'";
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
