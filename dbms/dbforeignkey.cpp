#include "dbforeignkey.h"
#include "appconst.h"
#include "appconst.h"
#include "qsqlqueryhelper.h"


DBForeignKey::DBForeignKey(QString caption, QObject *parent)
  : DBConstraintItem(caption, parent)
{
  registerField(F_REFTABLE);
  registerField(F_REFCOLUMN);
  registerField(F_ON_UPDATE);
  registerField(F_ON_DELETE);
}

int DBForeignKey::type()
{
  return DBObjectItem::ForeignKey;
}

ActionResult DBForeignKey::insertMe()
{
  QString sql = "alter table #table# add constraint #caption# "
                "foreign key (#column#) references #reftable#(#refcolumn#) "
                "on update #onUpdate# on delete #onDelete#";
  QString preparedSql = fillPatternWithFields(sql);
  return execSql(preparedSql, connectionName());
}


bool DBForeignKey::refresh()
{
  QString sql =
      "select kc.table_name \"table\", kc.column_name \"column\", rc.table_name \"reftable\", "
      "rc.column_name \"refcolumn\", ac.update_rule \"onUpdate\", ac.delete_rule \"onDelete\""
      "from information_schema.key_column_usage kc "
      "left join information_schema.constraint_column_usage rc on kc.constraint_name=rc.constraint_name "
      "left join information_schema.referential_constraints ac on kc.constraint_name=ac.constraint_name "
      "where kc.constraint_name='#caption#'";
  QString preparedSql = fillSqlPattern(sql);
  QSqlQuery resultSet = QSqlQueryHelper::execSql(preparedSql, connectionName());
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
