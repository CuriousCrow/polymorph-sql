#include "firebirdforeignkey.h"
#include "objects/appconst.h"
#include "utils/sqlqueryhelper.h"

FirebirdForeignKey::FirebirdForeignKey()
  : DBForeignKey("", Q_NULLPTR)
{
}

bool FirebirdForeignKey::refresh()
{
  QString sql =
      "SELECT DISTINCT "
//      "rc.RDB$CONSTRAINT_NAME AS \"name\", "
      "trim(rc.RDB$RELATION_NAME) AS \"table\", "
      "trim(d1.RDB$FIELD_NAME) AS \"column\", "
      "trim(d2.RDB$DEPENDED_ON_NAME) AS \"reftable\", "
      "trim(d2.RDB$FIELD_NAME) AS \"refcolumn\", "
      "trim(refc.RDB$UPDATE_RULE) AS \"onUpdate\", "
      "trim(refc.RDB$DELETE_RULE) AS \"onDelete\" "
      "FROM RDB$RELATION_CONSTRAINTS AS rc "
      "LEFT JOIN RDB$REF_CONSTRAINTS refc ON rc.RDB$CONSTRAINT_NAME = refc.RDB$CONSTRAINT_NAME "
      "LEFT JOIN RDB$DEPENDENCIES d1 ON d1.RDB$DEPENDED_ON_NAME = rc.RDB$RELATION_NAME "
      "LEFT JOIN RDB$DEPENDENCIES d2 ON d1.RDB$DEPENDENT_NAME = d2.RDB$DEPENDENT_NAME "
      "WHERE rc.RDB$CONSTRAINT_TYPE = 'FOREIGN KEY' "
      "AND d1.RDB$DEPENDED_ON_NAME <> d2.RDB$DEPENDED_ON_NAME "
      "AND d1.RDB$FIELD_NAME <> d2.RDB$FIELD_NAME "
      "AND rc.RDB$CONSTRAINT_NAME = '#caption#'";
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
