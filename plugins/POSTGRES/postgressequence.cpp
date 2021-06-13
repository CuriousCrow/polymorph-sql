#include "postgressequence.h"
#include "sdk/utils/qsqlqueryhelper.h"
#include "sdk/objects/appconst.h"


PostgresSequence::PostgresSequence()
  : DBSequenceItem()
{

}

bool PostgresSequence::refresh()
{
  QString sql = "SELECT sequence_name \"caption\", start_value \"startValue\", minimum_value \"minValue\", maximum_value \"maxValue\", increment \"step\" "
                "FROM information_schema.sequences where sequence_name='#caption#'";
  QString preparedSql = fillSqlPattern(sql);
  QSqlQuery resultSet = QSqlQueryHelper::execSql(preparedSql, connectionName());
  if (resultSet.next()) {
    setFieldValue(F_CAPTION, resultSet.value(F_CAPTION));
    setFieldValue(F_MIN_VALUE, resultSet.value(F_MIN_VALUE).toInt());
    setFieldValue(F_MAX_VALUE, resultSet.value(F_MAX_VALUE).toInt());
    setFieldValue(F_STEP, resultSet.value(F_STEP).toInt());
    setFieldValue(F_START_VALUE, resultSet.value(F_START_VALUE).toInt());

    sql = "select * FROM \"#caption#\"";
    preparedSql = fillSqlPattern(sql);
    resultSet = QSqlQueryHelper::execSql(preparedSql, connectionName());
    if (resultSet.next()) {
      setFieldValue(F_CURRENT_VALUE, resultSet.value(0).toInt());
      field(F_CURRENT_VALUE).submit();
    }
    submit();
    return true;
  }
  else {
    return false;
  }
}
