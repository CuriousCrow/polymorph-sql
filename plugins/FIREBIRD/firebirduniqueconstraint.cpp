#include "firebirduniqueconstraint.h"
#include "objects/appconst.h"
#include "utils/sqlqueryhelper.h"

FirebirdUniqueConstraint::FirebirdUniqueConstraint(): DBUniqueConstraint("", Q_NULLPTR)
{
}


bool FirebirdUniqueConstraint::refresh()
{
  QString sql =
      "select trim(sg.rdb$field_name) \"column\" "
      "from rdb$index_segments sg "
      "left join rdb$relation_constraints rc on rc.rdb$index_name = sg.rdb$index_name "
      "where sg.rdb$index_name = '#caption#'";
  QString preparedSql = fillSqlPatternWithFields(sql);
  QSqlQuery resultSet = SqlQueryHelper::execSql(preparedSql, connectionName());
  QStringList columns;
  while (resultSet.next()) {
    columns.append(resultSet.value(F_COLUMN).toString());
  }
  //TODO: Check field column is not empty
  setFieldValue(F_COLUMN, columns.join(","));
  submit();
  return true;
}
