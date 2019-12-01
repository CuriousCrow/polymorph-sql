#include "qdbpostgreqfunctionitem.h"
#include "../appconst.h"
#include "../../qsqlqueryhelper.h"


DBPostgreqFunctionItem::DBPostgreqFunctionItem(QString caption, QObject *parent)
  : DBProcedureItem(caption, parent)
{
}


bool DBPostgreqFunctionItem::refresh()
{
  QString sql = "SELECT data_type \"returnType\", external_language \"language\", routine_definition \"sourceCode\" FROM information_schema.routines "
                "WHERE routine_type='FUNCTION' and specific_schema='public' "
                "and routine_name='#caption#'";
  QString preparedSql = fillSqlPattern(sql);
  QSqlQuery resultSet = QSqlQueryHelper::execSql(preparedSql, connectionName());
  if (resultSet.next()) {
    setFieldValue(F_SOURCE_CODE, resultSet.value(F_SOURCE_CODE));
    setFieldValue(F_LANGUAGE, resultSet.value(F_LANGUAGE));
    setFieldValue(F_RETURN_TYPE, resultSet.value(F_RETURN_TYPE));
    submit();
    return true;
  }
  else {
    return false;
  }
}

ActionResult DBPostgreqFunctionItem::insertMe()
{
  QString sql =
      "CREATE OR REPLACE FUNCTION #caption#() "
      "RETURNS #returnType# "
      "LANGUAGE '#language#' "
      "AS $BODY$#sourceCode#$BODY$";
  QString preparedSql = fillSqlPattern(sql);
  return execSql(preparedSql, connectionName());
}

ActionResult DBPostgreqFunctionItem::updateMe()
{
  return insertMe();
}

ActionResult DBPostgreqFunctionItem::deleteMe()
{
  QString sql = "DROP FUNCTION \"#caption#\"";
  QString preparedSql = fillSqlPattern(sql);
  return execSql(preparedSql, connectionName());
}
