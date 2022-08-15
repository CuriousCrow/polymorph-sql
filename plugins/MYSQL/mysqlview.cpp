#include "mysqlview.h"
#include "objects/appconst.h"
#include "utils/sqlqueryhelper.h"


MysqlView::MysqlView() : DBViewItem()
{
}

bool MysqlView::refresh()
{
  QString sql =
      "SELECT VIEW_DEFINITION \"queryText\" FROM INFORMATION_SCHEMA.VIEWS "
      "where TABLE_SCHEMA = '#databaseName#' and TABLE_NAME = '#caption#'";
  QString preparedSql = fillSqlPatternWithFields(sql);
  QSqlQuery resultSet = SqlQueryHelper::execSql(preparedSql, connectionName());
  if (resultSet.next()) {
    setFieldValue(F_QUERY_TEXT, resultSet.value(F_QUERY_TEXT));
    submit();
    return true;
  }
  else {
    return false;
  }
}
