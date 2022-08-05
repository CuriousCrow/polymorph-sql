#include "dbcheckconstraint.h"
#include "appconst.h"
#include "utils/sqlqueryhelper.h"


DBCheckConstraint::DBCheckConstraint(QString caption, QObject *parent)
  : DBConstraintItem(caption, parent)
{
  registerField(F_EXPRESSION);
}

int DBCheckConstraint::type() const
{
  return DBObjectItem::CheckConstraint;
}

ActionResult DBCheckConstraint::insertMe()
{
  QString sql = "alter table \"#table#\" add constraint #caption# check (#expression#)";
  QString preparedSql = fillSqlPatternWithFields(sql);
  return execSql(preparedSql, connectionName());
}

bool DBCheckConstraint::refresh()
{
  return false;
}
