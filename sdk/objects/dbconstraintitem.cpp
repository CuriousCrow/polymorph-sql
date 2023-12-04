#include "dbconstraintitem.h"
#include "appconst.h"


DBConstraintItem::DBConstraintItem(QString caption, QObject *parent)
  : DBObjectItem(caption, parent)
{
  _identifierSupport = new QuoteIdentifier();
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
  QString sql = "alter table %1 drop constraint %2";
  QString preparedSql = sql.arg(_identifierSupport->escapeIdentifier(fieldValue(F_TABLE).toString()), identifier());
  return execSql(preparedSql, connectionName());
}


ActionResult DBConstraintItem::updateMe()
{
  return ActionResult(ERR_NOT_IMPLEMENTED);
}

QString DBConstraintItem::fillSqlPatternWithFields(QString pattern) const
{
  QString sql = pattern.replace("#table#", _identifierSupport->escapeIdentifier(fieldValue(F_TABLE).toString()));
  return DBObjectItem::fillSqlPatternWithFields(sql);
}
