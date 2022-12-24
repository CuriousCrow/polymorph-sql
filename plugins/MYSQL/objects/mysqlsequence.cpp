#include "mysqlsequence.h"
#include "utils/sqlqueryhelper.h"
#include "objects/appconst.h"

MysqlSequence::MysqlSequence() : DBSequenceItem()
{
  _identifierSupport = new BacktickIdentifier();
}


bool MysqlSequence::refresh()
{
    QString sql = "ANALYZE TABLE `#caption#`";
    QString preparedSql = fillSqlPatternWithFields(sql);
    //Problem of non-updating autoincrement values solved by information_schema_stats_expiry global parameter
    //ANALYLE TABLE doesn`t work for InnoDB tables
//    SqlQueryHelper::execSql(preparedSql, connectionName());
    sql = "SELECT AUTO_INCREMENT 'currentValue' FROM INFORMATION_SCHEMA.TABLES "
        "WHERE TABLE_SCHEMA='#databaseName#' AND TABLE_NAME='#caption#'";
    preparedSql = fillSqlPatternWithFields(sql);
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
