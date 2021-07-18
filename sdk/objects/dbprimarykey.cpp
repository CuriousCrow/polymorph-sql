#include "dbprimarykey.h"
#include "appconst.h"
#include "../utils/qsqlqueryhelper.h"


DBPrimaryKey::DBPrimaryKey(QString caption, QObject *parent)
  : DBConstraintItem(caption, parent)
{

}

int DBPrimaryKey::type() const
{
  return DBObjectItem::PrimaryKey;
}

bool DBPrimaryKey::refresh()
{
  return false;
}

ActionResult DBPrimaryKey::insertMe()
{
  QString sql = "alter table #table# add constraint #caption# primary key (#column#)";
  QString preparedSql = fillSqlPatternWithFields(sql);
  return execSql(preparedSql, connectionName());
}
