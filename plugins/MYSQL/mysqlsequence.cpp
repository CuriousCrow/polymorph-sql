#include "mysqlsequence.h"
#include "utils/sqlqueryhelper.h"
#include "objects/appconst.h"

MysqlSequence::MysqlSequence() : DBSequenceItem()
{
}


bool MysqlSequence::refresh()
{
    QString sql = "SELECT AUTO_INCREMENT 'currentValue' FROM INFORMATION_SCHEMA.TABLES "
        "WHERE TABLE_SCHEMA='#databaseName#' AND TABLE_NAME='#caption#'";
    QString preparedSql = fillSqlPatternWithFields(sql);
    QSqlQuery resultSet = SqlQueryHelper::execSql(preparedSql, connectionName());
    if (resultSet.next()) {
      setFieldValue(F_CURRENT_VALUE, resultSet.value(0).toInt());
      field(F_CURRENT_VALUE).submit();
      submit();
      return true;
    }
    else {
      return false;
    }
}
