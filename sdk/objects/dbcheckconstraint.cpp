#include "dbcheckconstraint.h"
#include "appconst.h"


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
  return execSql(toDDL(), connectionName());
}

QString DBCheckConstraint::toDDL() const
{
  QString sql = "alter table #table# add constraint #caption# check (#expression#)";
  return fillSqlPatternWithFields(sql);
}

bool DBCheckConstraint::refresh()
{
  return false;
}
