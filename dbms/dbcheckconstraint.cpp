#include "dbcheckconstraint.h"
#include "appconst.h"
#include "qsqlqueryhelper.h"


DBCheckConstraint::DBCheckConstraint(QString caption, QObject *parent)
  : DBConstraintItem(caption, parent)
{
  registerField(F_EXPRESSION);
}

int DBCheckConstraint::type()
{
  return DBObjectItem::CheckConstraint;
}

ActionResult DBCheckConstraint::insertMe()
{
  QString sql = "alter table #table# add constraint #caption# check (#expression#)";
  QString preparedSql = fillPatternWithFields(sql);
  return execSql(preparedSql, connectionName());
}

bool DBCheckConstraint::refresh()
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
