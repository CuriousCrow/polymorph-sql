#include "postgresforeignkey.h"
#include "utils/sqlqueryhelper.h"

#include "objects/appconst.h"

PostgresForeignKey::PostgresForeignKey()
  : DBForeignKey("", nullptr)
{

}


bool PostgresForeignKey::refresh()
{
  QString sql =
      "select kc.table_name \"table\", kc.column_name \"column\", rc.table_name \"reftable\", "
      "rc.column_name \"refcolumn\", ac.update_rule \"onUpdate\", ac.delete_rule \"onDelete\""
      "from information_schema.key_column_usage kc "
      "left join information_schema.constraint_column_usage rc on kc.constraint_name=rc.constraint_name "
      "left join information_schema.referential_constraints ac on kc.constraint_name=ac.constraint_name "
      "where kc.constraint_name='#caption#'";
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
