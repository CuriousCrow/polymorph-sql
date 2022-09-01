#include "mysqlprocedure.h"
#include "objects/appconst.h"
#include "utils/sqlqueryhelper.h"

MysqlProcedure::MysqlProcedure() : DBProcedureItem()
{
  _identifierSupport = new BacktickIdentifier();
  registerField(F_ARGS);

  _mArguments = new VariantMapTableModel();
  _mArguments->registerColumn(F_MODE, tr("Mode"));
  _mArguments->registerColumn(F_NAME, tr("Name"));
  _mArguments->registerColumn(F_TYPE, tr("Type"));
}

MysqlProcedure::~MysqlProcedure()
{
  delete _mArguments;
}


bool MysqlProcedure::refresh()
{
  QString sql = "select ROUTINE_NAME \"name\", ROUTINE_DEFINITION \"sourceCode\" "
  "from INFORMATION_SCHEMA.ROUTINES "
  "where ROUTINE_SCHEMA = '#databaseName#' and ROUTINE_NAME = '#caption#'";
  QString preparedSql = fillSqlPatternWithFields(sql);
  QSqlQuery resultSet = SqlQueryHelper::execSql(preparedSql, connectionName());
  if (resultSet.next()) {
    setFieldValue(F_SOURCE_CODE, resultSet.value(F_SOURCE_CODE));
    submit();

    refreshArguments();
    return true;
  }
  else {
    return false;
  }
}

QString MysqlProcedure::toDDL() const
{
  QString sql =
      "CREATE PROCEDURE #caption#(%1)\n"
      "BEGIN\n#sourceCode#\nEND";
  QString preparedSql = fillSqlPatternWithFields(sql);
  return preparedSql.arg(argsFromModel());
}

ActionResult MysqlProcedure::insertMe()
{
  QString sql = toDDL();
  return execSql(sql, connectionName());
}

VariantMapTableModel *MysqlProcedure::argumentModel()
{
  return _mArguments;
}

void MysqlProcedure::refreshArguments()
{
  _mArguments->clear();
  QString sql = "select PARAMETER_NAME name, PARAMETER_MODE mode, DTD_IDENTIFIER type "
                "from information_schema.parameters "
                "where specific_schema = '#databaseName#' and specific_name = '#caption#' "
                "order by ordinal_position";
  QString preparedSql = fillSqlPatternWithFields(sql);
  QSqlQuery resultSet = SqlQueryHelper::execSql(preparedSql, connectionName());
  int id = 1;
  while (resultSet.next()) {
    QVariantMap row;
    row.insert(F_ID, id++);
    row.insert(F_NAME, resultSet.value(F_NAME));
    row.insert(F_MODE, resultSet.value(F_MODE));
    row.insert(F_TYPE, resultSet.value(F_TYPE));
    _mArguments->addRow(row);
  }
}

QString MysqlProcedure::argsFromModel() const
{
  QStringList args;
  for(int row = 0; row < _mArguments->rowCount(); row++) {
    QString line = _mArguments->data(row, F_MODE).toString() + " "
      + _mArguments->data(row, F_NAME).toString() + " "
      + _mArguments->data(row, F_TYPE).toString();
    args.append(line);
  }
  return args.join(", ");
}
