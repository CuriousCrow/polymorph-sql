#include "dbuniqueconstraint.h"
#include "qsqlqueryhelper.h"
#include "appconst.h"


DBUniqueConstraint::DBUniqueConstraint(QString caption, QObject *parent)
  : DBConstraintItem(caption, parent)
{

}

int DBUniqueConstraint::type()
{
  return DBObjectItem::UniqueConstraint;
}

ActionResult DBUniqueConstraint::insertMe()
{
  QString sql = "alter table #table# add constraint #caption# unique (#column#)";
  QString preparedSql = fillPatternWithFields(sql);
  return execSql(preparedSql, connectionName());
}


bool DBUniqueConstraint::refresh()
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
