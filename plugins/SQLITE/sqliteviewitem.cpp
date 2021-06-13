#include "sqliteviewitem.h"
#include "sdk/objects/appconst.h"
#include "sdk/utils/qsqlqueryhelper.h"


SqliteViewItem::SqliteViewItem()
  : DBViewItem()
{
}

bool SqliteViewItem::refresh()
{
  QString sql =
      "select name, sql from sqlite_master where type = 'view' "
      "and name='#caption#'";
  QString preparedSql = fillSqlPattern(sql);
  QSqlQuery resultSet = QSqlQueryHelper::execSql(preparedSql, connectionName());
  if (resultSet.next()) {
    setFieldValue(F_QUERY_TEXT, resultSet.value("sql"));
    submit();
    return true;
  }
  else {
    return false;
  }
}
