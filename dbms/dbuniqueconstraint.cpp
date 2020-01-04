#include "dbuniqueconstraint.h"
#include "qsqlqueryhelper.h"
#include "appconst.h"


DBUniqueConstraint::DBUniqueConstraint(QString caption, QObject *parent)
  : DBConstraintItem(caption, parent)
{

}

int DBUniqueConstraint::type()
{
  return DBObjectItem::UniqueConstraint;
}

ActionResult DBUniqueConstraint::insertMe()
{
  QString sql = "alter table #table# add constraint #caption# unique (#column#)";
  QString preparedSql = fillPatternWithFields(sql);
  return execSql(preparedSql, connectionName());
}


bool DBUniqueConstraint::refresh()
{
  return false;
}