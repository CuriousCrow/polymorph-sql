#include "dbprimarykey.h"
#include "appconst.h"
#include "qsqlqueryhelper.h"


DBPrimaryKey::DBPrimaryKey(QString caption, QObject *parent)
  : DBConstraintItem(caption, parent)
{

}

int DBPrimaryKey::type()
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
  QString preparedSql = fillPatternWithFields(sql);
  return execSql(preparedSql, connectionName());
}
