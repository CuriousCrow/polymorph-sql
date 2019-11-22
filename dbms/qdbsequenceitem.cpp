#include "qdbsequenceitem.h"
#include "dbms/appconst.h"
#include "qsqlqueryhelper.h"
#include <QIcon>


QDBSequenceItem::QDBSequenceItem(QString caption, QObject *parent):
  QDBObjectItem(caption, parent)
{
  registerField(F_CURRENT_VALUE);
  registerField(F_MIN_VALUE);
  registerField(F_MAX_VALUE);
  registerField(F_STEP);
  registerField(F_START_VALUE);
}

QDBSequenceItem::~QDBSequenceItem()
{
}

int QDBSequenceItem::colCount()
{
  return 1;
}

QVariant QDBSequenceItem::colData(int column, int role)
{
  Q_UNUSED(column)

  switch (role) {
  case Qt::DisplayRole:
    return fieldValue(F_CAPTION);
  case Qt::DecorationRole:
    return QIcon(":/icons/sequence.png");
  default:
    return QVariant();
  }
}

bool QDBSequenceItem::loadChildren()
{
  return true;
}

int QDBSequenceItem::type()
{
  return Sequence;
}

bool QDBSequenceItem::insertMe()
{
  QString sql = "CREATE SEQUENCE \"" + fieldValue(F_CAPTION).toString() + "\" {INCREMENT #step# }"
      "{MINVALUE #minValue# }{MAXVALUE #maxValue# }{START WITH #startValue#}";
  QString preparedSql = fillWithModifiedFields(sql);
  return !QSqlQueryHelper::execSql(preparedSql, connectionName()).lastError().isValid();
}

bool QDBSequenceItem::updateMe()
{
  QString sql = "ALTER SEQUENCE \"" + fieldValue(F_CAPTION).toString() + "\" {INCREMENT BY #step# }{MINVALUE #minValue# }"
      "{MAXVALUE #maxValue# }{START WITH #startValue# }{RESTART WITH #currentValue#}";
  QString preparedSql = fillWithModifiedFields(sql);
  return !QSqlQueryHelper::execSql(preparedSql, connectionName()).lastError().isValid();
}

bool QDBSequenceItem::deleteMe()
{
  QString sql = "DROP SEQUENCE \"#caption#\"";
  QString preparedSql = fillSqlPattern(sql);
  return !QSqlQueryHelper::execSql(preparedSql, connectionName()).lastError().isValid();
}
