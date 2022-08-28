#include "firebirdprocedure.h"
#include "objects/appconst.h"
#include "utils/sqlqueryhelper.h"
#include "firebirdutils.h"

FirebirdProcedure::FirebirdProcedure() : DBProcedureItem()
{
  _identifierSupport = new QuoteIdentifier();
  registerField(F_ARGS);
}

FirebirdProcedure::~FirebirdProcedure()
{
  delete _identifierSupport;
}

ArgumentTableModel *FirebirdProcedure::inArgumentModel()
{
  return _inArgModel;
}

ArgumentTableModel *FirebirdProcedure::outArgumentModel()
{
  return _outArgModel;
}

void FirebirdProcedure::addInArg()
{
  QVariantMap rowArg;
  rowArg.insert(F_ID, _inMaxId++);
  _inArgModel->addRow(rowArg);
}

void FirebirdProcedure::addOutArg()
{
  QVariantMap rowArg;
  rowArg.insert(F_ID, _outMaxId++);
  _outArgModel->addRow(rowArg);
}

void FirebirdProcedure::removeInArg(int row)
{
  _inArgModel->deleteByRow(row);
}

void FirebirdProcedure::removeOutArg(int row)
{
  _outArgModel->deleteByRow(row);
}


bool FirebirdProcedure::refresh()
{
  _inArgModel->clear();
  _outArgModel->clear();

  QString sql = "select p.rdb$procedure_source \"sourceCode\", trim(pp.rdb$parameter_name) \"name\", "
          "pp.rdb$parameter_type \"mode\",  trim(f.rdb$field_type) \"type\", f.rdb$character_length \"length\", "
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
      row.insert(F_LENGTH, resultSet.value(F_LENGTH));

      if (mode == 0) {
        _inArgModel->addRow(row);
      } else {
        _outArgModel->addRow(row);
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
  QString inArgs = argsFromModel(_inArgModel);
  if (!inArgs.isEmpty())
    args += " (" + inArgs + ")";
  QString outArgs = argsFromModel(_outArgModel);
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

ArgumentTableModel::ArgumentTableModel() : VariantMapTableModel()
{
  this->registerColumn(F_NAME, tr("Name"));
  this->registerColumn(F_TYPE, tr("Type"));
  this->registerColumn(F_LENGTH, tr("Length"));

  connect(this, &ArgumentTableModel::dataChanged, this, &ArgumentTableModel::onDataChanged);
}


void ArgumentTableModel::onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
  Q_UNUSED(bottomRight)

  if (topLeft.column() == 1) {
    QString typeName = topLeft.data().toString();
    DBType* type = _firebirdTypeProvider->type(typeName);
    if (!type->hasLength())
      setData(index(topLeft.row(), 2), QVariant(), Qt::EditRole);
  }
}
