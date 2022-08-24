#include "firebirddomain.h"
#include <QIcon>
#include <QDebug>
#include "objects/appconst.h"
#include "utils/sqlqueryhelper.h"
#include "firebirdutils.h"

FirebirdDomain::FirebirdDomain() : DBUserType()
{
  registerField(F_TYPE);
  registerField(F_LENGTH);
  registerField(F_DEFAULT);
  registerField(F_NOT_NULL);
}


QString FirebirdDomain::toDDL() const
{
  QString sql = "CREATE DOMAIN #caption# AS %1";
  QString type = fieldValue(F_TYPE).toString();
  if (!isEmptyField(F_LENGTH))
    type = type.append("(").append(fieldValue(F_LENGTH).toString()).append(") ");
  if (!isEmptyField(F_DEFAULT))
    type = type.append(" DEFAULT ").append(fieldValue(F_DEFAULT).toString());
  if (!isEmptyField(F_NOT_NULL) && fieldValue(F_NOT_NULL).toBool())
    type = type.append(" NOT NULL");
  sql = sql.arg(type);
  return fillSqlPatternWithFields(sql);
}

ActionResult FirebirdDomain::insertMe()
{
  qDebug() << "Create domain" << caption();
  QString sql = toDDL();
  return execSql(sql, connectionName());
}

ActionResult FirebirdDomain::deleteMe()
{
  QString sql = "drop domain #identifier#";
  QString preparedSql = fillSqlPatternWithFields(sql);
  return execSql(preparedSql, connectionName());
}

int FirebirdDomain::colCount() const
{
  return 1;
}

QVariant FirebirdDomain::colData(int column, int role) const
{
  Q_UNUSED(column)

  switch (role) {
  case Qt::DisplayRole:
    return caption();
  case Qt::DecorationRole:
    return QIcon(":/icons/trigger.png");
  default:
    return QVariant();
  }
}

bool FirebirdDomain::refresh()
{
  QString sql = "select RDB$FIELD_NAME \"name\", RDB$DEFAULT_SOURCE \"default\", "
                "RDB$FIELD_TYPE \"code\", RDB$CHARACTER_LENGTH \"length\""
                "from rdb$fields where rdb$field_name='#caption#'";
  QString preparedSql = fillSqlPatternWithFields(sql);
  qDebug() << preparedSql;
  QSqlQuery resultSet = SqlQueryHelper::execSql(preparedSql, connectionName());
  if (resultSet.next()) {
    setFieldValue(F_DEFAULT, resultSet.value(F_DEFAULT).toString().replace("DEFAULT ", ""));
    int code = resultSet.value("code").toInt();
    setFieldValue(F_TYPE, Utils::typeFromCode(code));
    setFieldValue(F_LENGTH, resultSet.value(F_LENGTH).toInt());
    submit();
    return true;
  }
  else {
    return false;
  }
}
