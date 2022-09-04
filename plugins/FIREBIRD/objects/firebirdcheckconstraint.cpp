#include "firebirdcheckconstraint.h"
#include "utils/sqlqueryhelper.h"
#include "objects/appconst.h"

FirebirdCheckConstraint::FirebirdCheckConstraint()
  : DBCheckConstraint("", Q_NULLPTR)
{

}

bool FirebirdCheckConstraint::refresh()
{
  QString sql = "select t.RDB$RELATION_NAME \"table\", t.RDB$TRIGGER_SOURCE \"expression\" "
    "from RDB$CHECK_CONSTRAINTS cc "
    "left join RDB$TRIGGERS t on cc.RDB$TRIGGER_NAME = t.RDB$TRIGGER_NAME "
    "where cc.RDB$CONSTRAINT_NAME = '#caption#' AND t.RDB$TRIGGER_TYPE = 1";
  QString preparedSql = fillSqlPatternWithFields(sql);
  QSqlQuery resultSet = SqlQueryHelper::execSql(preparedSql, connectionName());
  if (resultSet.next()) {
    setFieldValue(F_TABLE, resultSet.value(F_TABLE));
    setFieldValue(F_EXPRESSION, resultSet.value(F_EXPRESSION));
    submit();
    return true;
  }
  else {
    return false;
  }
}
