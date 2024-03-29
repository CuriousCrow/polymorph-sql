#include "postgresview.h"

#include "objects/appconst.h"
#include "utils/sqlqueryhelper.h"

#include <QDebug>


PostgresViewItem::PostgresViewItem()
  : DBViewItem()
{
}

bool PostgresViewItem::refresh()
{
  QString sql =
      "select table_name \"name\", view_definition \"queryText\" "
      "from INFORMATION_SCHEMA.views where table_schema='public' "
      "and table_name='#caption#'";
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
