#include "dbprimarykey.h"
#include "appconst.h"
#include "utils/sqlqueryhelper.h"


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
  return execSql(toDDL(), connectionName());
}


QString DBPrimaryKey::toDDL() const
{
  QString sql = "alter table #table# add constraint #caption# primary key (#column#)";
  return fillSqlPatternWithFields(sql);
}
