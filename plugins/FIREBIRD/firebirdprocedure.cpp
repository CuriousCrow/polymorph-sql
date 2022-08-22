#include "firebirdprocedure.h"
#include "objects/appconst.h"
#include "utils/sqlqueryhelper.h"
#include "firebirdutils.h"

FirebirdProcedure::FirebirdProcedure() : DBProcedureItem()
{
  _identifierSupport = new QuoteIdentifier();
  registerField(F_ARGS);

  _mInArguments = new VariantMapTableModel();
  _mInArguments->registerColumn(F_NAME, tr("Name"));
  _mInArguments->registerColumn(F_TYPE, tr("Type"));

  _mOutArguments = new VariantMapTableModel();
  _mOutArguments->registerColumn(F_NAME, tr("Name"));
  _mOutArguments->registerColumn(F_TYPE, tr("Type"));
}

FirebirdProcedure::~FirebirdProcedure()
{
  delete _identifierSupport;
  delete _mInArguments;
  delete _mOutArguments;
}

VariantMapTableModel *FirebirdProcedure::inArgModel()
{
  return _mInArguments;
}

VariantMapTableModel *FirebirdProcedure::outArgModel()
{
  return _mOutArguments;
}

void FirebirdProcedure::addInArg()
{
  QVariantMap rowArg;
  rowArg.insert(F_ID, _inMaxId++);
  _mInArguments->addRow(rowArg);
}

void FirebirdProcedure::addOutArg()
{
  QVariantMap rowArg;
  rowArg.insert(F_ID, _outMaxId++);
  _mOutArguments->addRow(rowArg);
}

void FirebirdProcedure::removeInArg(int row)
{
  _mInArguments->deleteByRow(row);
}

void FirebirdProcedure::removeOutArg(int row)
{
  _mOutArguments->deleteByRow(row);
}


bool FirebirdProcedure::refresh()
{
  _mInArguments->clear();
  _mOutArguments->clear();

  QString sql = "select p.rdb$procedure_source \"sourceCode\", pp.rdb$parameter_name \"name\", "
          "pp.rdb$parameter_type \"mode\",  f.rdb$field_type \"type\", f.rdb$character_length \"length\", "
          "f.rdb$field_precision \"precision\" "
          "from rdb$procedures p "
          "left join rdb$procedure_parameters pp on p.rdb$procedure_name = pp.rdb$procedure_name "
          "left join rdb$fields f on pp.rdb$field_source = f.rdb$field_name "
          "where p.rdb$procedure_name = '#caption#'"
          "order by pp.rdb$parameter_type, pp.rdb$parameter_number";
  QString preparedSql = fillSqlPatternWithFields(sql);
  QSqlQuery resultSet = SqlQueryHelper::execSql(preparedSql, connectionName());
  if (resultSet.next()) {
    setFieldValue(F_SOURCE_CODE, resultSet.value(F_SOURCE_CODE));
    submit();

    forever {
      if (resultSet.value(F_NAME).isNull())
        break;

      int mode = resultSet.value(F_MODE).toInt();
      QVariantMap row;
      row.insert(F_ID, mode == 0 ? _inMaxId++ : _outMaxId++);
      row.insert(F_NAME, resultSet.value(F_NAME));
      row.insert(F_TYPE, Utils::typeFromCode(resultSet.value(F_TYPE).toInt()));

      if (mode == 0) {
        _mInArguments->addRow(row);
      } else {
        _mOutArguments->addRow(row);
      }

      if (!resultSet.next())
        break;
    }
    return true;
  }
  else {
    return false;
  }
}

QString FirebirdProcedure::toDDL() const
{
  QString sql = "RECREATE PROCEDURE #identifier# %1\n"
  "AS\n#sourceCode#";

  QString preparedSql = fillSqlPatternWithFields(sql);
  QString args = "";
  QString inArgs = argsFromModel(_mInArguments);
  if (!inArgs.isEmpty())
    args += " (" + inArgs + ")";
  QString outArgs = argsFromModel(_mOutArguments);
  if (!outArgs.isEmpty())
    args += " RETURNS(" + outArgs + ")";
  return preparedSql.arg(args);
}

ActionResult FirebirdProcedure::insertMe()
{ 
  QString sql = toDDL();
  return execSql(sql, connectionName());
}

ActionResult FirebirdProcedure::updateMe()
{
  return insertMe();
}

QString FirebirdProcedure::argsFromModel(VariantMapTableModel *argModel) const
{
  QStringList args;
  for(int row = 0; row < argModel->rowCount(); row++) {
    QString line = argModel->data(row, F_NAME).toString() + " "
      + argModel->data(row, F_TYPE).toString();
    args.append(line);
  }
  return args.join(", ");
}
