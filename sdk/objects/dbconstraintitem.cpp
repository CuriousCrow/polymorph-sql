#include "dbconstraintitem.h"
#include "appconst.h"


DBConstraintItem::DBConstraintItem(QString caption, QObject *parent)
  : DBObjectItem(caption, parent)
{
  registerField(F_TABLE);
  registerField(F_COLUMN);
}


bool DBConstraintItem::reloadChildren()
{
  return false;
}

int DBConstraintItem::type() const
{
  return DBObjectItem::Constraint;
}

ActionResult DBConstraintItem::deleteMe()
{
  QString sql = "alter table \"#table#\" drop constraint \"#caption#\"";
  QString preparedSql = fillSqlPatternWithFields(sql);
  return execSql(preparedSql, connectionName());
}


ActionResult DBConstraintItem::updateMe()
{
  return ActionResult(ERR_NOT_IMPLEMENTED);
}
