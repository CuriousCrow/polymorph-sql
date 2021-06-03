#include "postgresviewitem.h"
#include "../../qsqlqueryhelper.h"
#include "sdk/objects/appconst.h"
#include <QDebug>


PostgresViewItem::PostgresViewItem(QString caption, QObject *parent)
  : DBViewItem(caption, parent)
{
}

bool PostgresViewItem::refresh()
{
  QString sql =
      "select table_name \"name\", view_definition \"queryText\" "
      "from INFORMATION_SCHEMA.views where table_schema='public' "
      "and table_name='#caption#'";
  QString preparedSql = fillSqlPattern(sql);
  QSqlQuery resultSet = QSqlQueryHelper::execSql(preparedSql, connectionName());
  if (resultSet.next()) {
    setFieldValue(F_QUERY_TEXT, resultSet.value(F_QUERY_TEXT));
    submit();
    return true;
  }
  else {
    return false;
  }
}
