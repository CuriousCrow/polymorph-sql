#include "dbsequence.h"
#include "appconst.h"
#include <QIcon>


DBSequenceItem::DBSequenceItem():
  DBObjectItem("", nullptr)
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

int DBSequenceItem::colCount() const
{
  return 1;
}

QVariant DBSequenceItem::colData(int column, int role) const
{
  Q_UNUSED(column)

  switch (role) {
  case Qt::DisplayRole:
    return caption();
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

int DBSequenceItem::type() const
{
  return Sequence;
}

ActionResult DBSequenceItem::insertMe()
{
  QString sql = toDDL();
  return execSql(sql, connectionName());
}

ActionResult DBSequenceItem::updateMe()
{
  if (!isModified())
    return ActionResult(RES_OK_CODE, "Sequence is not modified");

  if (fieldModified(F_CAPTION)) {
    QString sql = "ALTER SEQUENCE \"#caption.old#\" RENAME TO \"#caption.new#\"";
    QString preparedSql = fillWithModifiedFields(sql);
    ActionResult actRes = execSql(preparedSql, connectionName());
    if (!actRes.isSuccess())
      return actRes;
    field(F_CAPTION).submit();
  }
  if (!isModified())
    return ActionResult(RES_OK_CODE, "Sequence is not modified");
  QString sql = "ALTER SEQUENCE \"" + caption() + "\" {INCREMENT BY #step# }{MINVALUE #minValue# }"
      "{MAXVALUE #maxValue# }{START WITH #startValue# }{RESTART WITH #currentValue#}";
  QString preparedSql = fillWithModifiedFields(sql);
  return execSql(preparedSql, connectionName());
}

ActionResult DBSequenceItem::deleteMe()
{
  QString sql = "DROP SEQUENCE \"#caption#\"";
  QString preparedSql = fillSqlPatternWithFields(sql);
  return execSql(preparedSql, connectionName());
}

QString DBSequenceItem::toDDL() const
{
  QString sql = "CREATE SEQUENCE \"" + caption() + "\" INCREMENT #step# "
      "MINVALUE #minValue# MAXVALUE #maxValue# START WITH #startValue#";
  QString preparedSql = fillSqlPatternWithFields(sql);
  return preparedSql;
}
