#include "qdbtriggeritem.h"
#include "qsqlqueryhelper.h"


QDBTriggerItem::QDBTriggerItem(QString caption, QObject *parent):
  QDBObjectItem(caption, parent)
{
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
  switch (role) {
  case Qt::DisplayRole:
    return fieldValue("caption");
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

bool QDBTriggerItem::insertMe()
{
    return true;
}

bool QDBTriggerItem::updateMe()
{
    return true;
}

bool QDBTriggerItem::deleteMe()
{
    QString sql = "drop trigger #caption#";
    QString preparedSql = fillSqlPattern(sql);
    return !QSqlQueryHelper::execSql(preparedSql, connectionName()).lastError().isValid();
}