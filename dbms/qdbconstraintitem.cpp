#include "qdbconstraintitem.h"
#include "appconst.h"


QDBConstraintItem::QDBConstraintItem(QString caption, QObject *parent)
  : QDBObjectItem(caption, parent)
{
  registerField(F_TABLE);
  registerField(F_COLUMN);
}


bool QDBConstraintItem::loadChildren()
{
  return false;
}

int QDBConstraintItem::type()
{
  return QDBObjectItem::Constraint;
}

ActionResult QDBConstraintItem::deleteMe()
{
  QString sql = "alter table \"#table#\" drop constraint \"#caption#\"";
  QString preparedSql = fillPatternWithFields(sql);
  return execSql(preparedSql, connectionName());
}


ActionResult QDBConstraintItem::updateMe()
{
  return ActionResult(ERR_NOT_IMPLEMENTED);
}
