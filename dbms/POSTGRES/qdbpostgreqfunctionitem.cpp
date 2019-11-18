#include "qdbpostgreqfunctionitem.h"
#include "../appconst.h"
#include "../../qsqlqueryhelper.h"


QDBPostgreqFunctionItem::QDBPostgreqFunctionItem(QString caption, QObject *parent)
  : QDBProcedureItem(caption, parent)
{
}


bool QDBPostgreqFunctionItem::refresh()
{
  QString sql = "SELECT routine_definition \"sourceCode\" FROM information_schema.routines "
                "WHERE routine_type='FUNCTION' and specific_schema='public' "
                "and routine_name='#caption#'";
  QString preparedSql = fillSqlPattern(sql);
  QSqlQuery resultSet = QSqlQueryHelper::execSql(preparedSql, connectionName());
  if (resultSet.next()) {
    setFieldValue(F_SOURCE_CODE, resultSet.value(F_SOURCE_CODE));
    submit();
    return true;
  }
  else {
    return false;
  }
}

bool QDBPostgreqFunctionItem::insertMe()
{
  return false;
}

bool QDBPostgreqFunctionItem::updateMe()
{
  return false;
}
