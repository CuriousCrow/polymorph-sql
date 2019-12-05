#include "dbprimarykey.h"
#include "appconst.h"
#include "qsqlqueryhelper.h"


DBPrimaryKey::DBPrimaryKey(QString caption, QObject *parent)
  : DBConstraintItem(caption, parent)
{

}

int DBPrimaryKey::type()
{
  return DBObjectItem::PrimaryKey;
}

bool DBPrimaryKey::refresh()
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

ActionResult DBPrimaryKey::insertMe()
{
  QString sql = "alter table #table# add constraint #caption# primary key (#column#)";
  QString preparedSql = fillPatternWithFields(sql);
  return execSql(preparedSql, connectionName());
}
