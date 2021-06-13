#include "dbtriggeritem.h"
#include "../utils/qsqlqueryhelper.h"
#include "appconst.h"
#include <QIcon>


DBTriggerItem::DBTriggerItem():
  DBObjectItem("", nullptr)
{
  registerField(F_EVENT_INSERT);
  registerField(F_EVENT_UPDATE);
  registerField(F_EVENT_DELETE);
  registerField(F_EVENT_TRUNCATE);
  registerField(F_TIMING);
  registerField(F_TABLE);
  registerField(F_FUNCTION);
  registerField(F_ENABLED);

  setFieldValue(F_EVENT_INSERT, false);
  setFieldValue(F_EVENT_UPDATE, false);
  setFieldValue(F_EVENT_DELETE, false);
  setFieldValue(F_EVENT_TRUNCATE, false);
}

DBTriggerItem::~DBTriggerItem()
{
}


int DBTriggerItem::colCount() const
{
  return 1;
}

QVariant DBTriggerItem::colData(int column, int role) const
{
  Q_UNUSED(column)

  switch (role) {
  case Qt::DisplayRole:
    return caption();
  case Qt::DecorationRole:
    return QIcon(":/icons/trigger.png");
  default:
    return QVariant();
  }
}

bool DBTriggerItem::reloadChildren()
{
  return true;
}

int DBTriggerItem::type() const
{
  return Trigger;
}

ActionResult DBTriggerItem::insertMe()
{
  return ActionResult(ERR_NOT_IMPLEMENTED);
}

ActionResult DBTriggerItem::updateMe()
{
  return ActionResult(ERR_NOT_IMPLEMENTED);
}

ActionResult DBTriggerItem::deleteMe()
{
  QString sql = "drop trigger #caption#";
  QString preparedSql = fillSqlPattern(sql);
  return execSql(preparedSql, connectionName());
}
