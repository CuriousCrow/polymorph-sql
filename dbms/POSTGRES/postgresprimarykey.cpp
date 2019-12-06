#include "postgresprimarykey.h"
#include "../../qsqlqueryhelper.h"
#include "../appconst.h"

PostgresPrimaryKey::PostgresPrimaryKey(QString caption, QObject *parent)
  : DBPrimaryKey(caption, parent)
{

}

bool PostgresPrimaryKey::refresh()
{
  QString sql = "select column_name \"column\" from information_schema.constraint_column_usage\n"
      "where constraint_name='#caption#'";
  QString preparedSql = fillSqlPattern(sql);
  QSqlQuery resultSet = QSqlQueryHelper::execSql(preparedSql, connectionName());
  QStringList columns;
  while (resultSet.next()) {
    columns.append(resultSet.value(F_COLUMN).toString());
  }
  //TODO: Check field column is not empty
  setFieldValue(F_COLUMN, columns.join(","));
  submit();
  return true;
}
