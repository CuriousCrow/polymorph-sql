#include "mysqlforeignkey.h"
#include "objects/appconst.h"
#include "utils/sqlqueryhelper.h"

MysqlForeignKey::MysqlForeignKey() : DBForeignKey("", Q_NULLPTR)
{
  _identifierSupport = new BacktickIdentifier();
}

bool MysqlForeignKey::refresh()
{
  QString sql =
      "select rc.TABLE_NAME \"table\", rc.REFERENCED_TABLE_NAME \"reftable\", "
      "cu.COLUMN_NAME \"column\", cu.REFERENCED_COLUMN_NAME \"refcolumn\", "
      "rc.UPDATE_RULE onUpdate, rc.DELETE_RULE onDelete\n"
      "from INFORMATION_SCHEMA.REFERENTIAL_CONSTRAINTS rc\n"
      "left join INFORMATION_SCHEMA.KEY_COLUMN_USAGE cu on rc.CONSTRAINT_NAME = cu.CONSTRAINT_NAME\n"
      "where rc.CONSTRAINT_SCHEMA = '#databaseName#' and rc.CONSTRAINT_NAME = '#caption#'";

  QString preparedSql = fillSqlPatternWithFields(sql);
  QSqlQuery resultSet = SqlQueryHelper::execSql(preparedSql, connectionName());
  if (resultSet.next()) {
    setFieldValue(F_TABLE, resultSet.value(F_TABLE));
    setFieldValue(F_COLUMN, resultSet.value(F_COLUMN));
    setFieldValue(F_REFTABLE, resultSet.value(F_REFTABLE));
    setFieldValue(F_REFCOLUMN, resultSet.value(F_REFCOLUMN));
    setFieldValue(F_ON_UPDATE, resultSet.value(F_ON_UPDATE));
    setFieldValue(F_ON_DELETE, resultSet.value(F_ON_DELETE));
    submit();
    return true;
  }
  else {
    return false;
  }
}
