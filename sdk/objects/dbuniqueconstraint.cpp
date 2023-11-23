#include "dbuniqueconstraint.h"
#include "utils/sqlqueryhelper.h"
#include "appconst.h"


DBUniqueConstraint::DBUniqueConstraint(QString caption, QObject *parent)
  : DBConstraintItem(caption, parent)
{
}

int DBUniqueConstraint::type() const
{
  return DBObjectItem::UniqueConstraint;
}

ActionResult DBUniqueConstraint::insertMe()
{
  return execSql(toDDL(), connectionName());
}

bool DBUniqueConstraint::refresh()
{
  return false;
}

QString DBUniqueConstraint::toDDL() const
{
  QString sql = "alter table #table# add constraint #caption# unique (#column#)";
  QString preparedSql = fillSqlPatternWithFields(sql);
  return preparedSql;
}
