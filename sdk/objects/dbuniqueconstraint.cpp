#include "dbuniqueconstraint.h"
#include "../utils/qsqlqueryhelper.h"
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
  QString sql = "alter table #table# add constraint #caption# unique (#column#)";
  QString preparedSql = fillSqlPatternWithFields(sql);
  return execSql(preparedSql, connectionName());
}


bool DBUniqueConstraint::refresh()
{
  return false;
}
