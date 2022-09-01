#include "firebirdview.h"
#include "objects/appconst.h"
#include "utils/sqlqueryhelper.h"

FirebirdView::FirebirdView() : DBViewItem()
{
}


bool FirebirdView::refresh()
{
  QString sql =
      "select RDB$VIEW_SOURCE \"queryText\" from RDB$RELATIONS "
      "where RDB$RELATION_NAME = '#caption#'";
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
