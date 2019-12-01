#include "qdbsequenceitem.h"
#include "dbms/appconst.h"
#include "qsqlqueryhelper.h"
#include <QIcon>


DBSequenceItem::DBSequenceItem(QString caption, QObject *parent):
  DBObjectItem(caption, parent)
{
  registerField(F_CURRENT_VALUE);
  registerField(F_MIN_VALUE);
  registerField(F_MAX_VALUE);
  registerField(F_STEP);
  registerField(F_START_VALUE);
}

DBSequenceItem::~DBSequenceItem()
{
}

int DBSequenceItem::colCount()
{
  return 1;
}

QVariant DBSequenceItem::colData(int column, int role)
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

bool DBSequenceItem::reloadChildren()
{
  return true;
}

int DBSequenceItem::type()
{
  return Sequence;
}

ActionResult DBSequenceItem::insertMe()
{
  QString sql = "CREATE SEQUENCE \"" + fieldValue(F_CAPTION).toString() + "\" {INCREMENT #step# }"
      "{MINVALUE #minValue# }{MAXVALUE #maxValue# }{START WITH #startValue#}";
  QString preparedSql = fillWithModifiedFields(sql);
  return execSql(preparedSql, connectionName());
}

ActionResult DBSequenceItem::updateMe()
{
  QString sql = "ALTER SEQUENCE \"" + fieldValue(F_CAPTION).toString() + "\" {INCREMENT BY #step# }{MINVALUE #minValue# }"
      "{MAXVALUE #maxValue# }{START WITH #startValue# }{RESTART WITH #currentValue#}";
  QString preparedSql = fillWithModifiedFields(sql);
  return execSql(preparedSql, connectionName());
}

ActionResult DBSequenceItem::deleteMe()
{
  QString sql = "DROP SEQUENCE \"#caption#\"";
  QString preparedSql = fillSqlPattern(sql);
  return execSql(preparedSql, connectionName());
}
