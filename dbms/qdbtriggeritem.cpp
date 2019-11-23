#include "qdbtriggeritem.h"
#include "qsqlqueryhelper.h"
#include "dbms/appconst.h"
#include <QIcon>


QDBTriggerItem::QDBTriggerItem(QString caption, QObject *parent):
  QDBObjectItem(caption, parent)
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

QDBTriggerItem::~QDBTriggerItem()
{
}


int QDBTriggerItem::colCount()
{
  return 1;
}

QVariant QDBTriggerItem::colData(int column, int role)
{
  Q_UNUSED(column)

  switch (role) {
  case Qt::DisplayRole:
    return fieldValue(F_CAPTION);
  case Qt::DecorationRole:
    return QIcon(":/icons/trigger.png");
  default:
    return QVariant();
  }
}

bool QDBTriggerItem::loadChildren()
{
  return true;
}

int QDBTriggerItem::type()
{
  return Trigger;
}

ActionResult QDBTriggerItem::insertMe()
{
  return ActionResult(ERR_NOT_IMPLEMENTED);
}

ActionResult QDBTriggerItem::updateMe()
{
  return ActionResult(ERR_NOT_IMPLEMENTED);
}

ActionResult QDBTriggerItem::deleteMe()
{
  QString sql = "drop trigger #caption#";
  QString preparedSql = fillSqlPattern(sql);
  return execSql(preparedSql, connectionName());
}
