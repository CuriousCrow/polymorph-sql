#include "dbprocedure.h"
#include "appconst.h"
#include <QIcon>

DBProcedureItem::DBProcedureItem():
  DBObjectItem("", nullptr)
{
  registerField(F_SOURCE_CODE);
  registerField(F_LANGUAGE);
  registerField(F_RETURN_TYPE);
}

DBProcedureItem::~DBProcedureItem()
{
}


int DBProcedureItem::colCount() const
{
  return 1;
}

QVariant DBProcedureItem::colData(int column, int role) const
{
  Q_UNUSED(column)

  switch (role) {
  case Qt::DisplayRole:
    return caption();
  case Qt::DecorationRole:
    return QIcon(":/icons/function.png");
  default:
    return QVariant();
  }
}

bool DBProcedureItem::reloadChildren()
{
  return true;
}

int DBProcedureItem::type() const
{
  return Procedure;
}


ActionResult DBProcedureItem::deleteMe()
{
  return execSql(dropDDL(), connectionName());
}

QString DBProcedureItem::dropDDL() const
{
  QString sql = "DROP PROCEDURE #identifier#";
  return fillSqlPatternWithFields(sql);
}
