#include "postgrescheckconstraint.h"
#include "../../qsqlqueryhelper.h"
#include "../appconst.h"


PostgresCheckConstraint::PostgresCheckConstraint(QString caption, QObject *parent)
  : DBCheckConstraint(caption, parent)
{

}

bool PostgresCheckConstraint::refresh()
{
  QString sql = "select check_clause \"expression\"\n"
      "from information_schema.check_constraints\n"
      "where constraint_name='#caption#'";
  QString preparedSql = fillSqlPattern(sql);
  QSqlQuery resultSet = QSqlQueryHelper::execSql(preparedSql, connectionName());
  if (resultSet.next()) {
    setFieldValue(F_EXPRESSION, resultSet.value(F_EXPRESSION));
    submit();
    return true;
  }
  else {
    return false;
  }
}
