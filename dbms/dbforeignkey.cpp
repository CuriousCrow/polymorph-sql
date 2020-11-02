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

int DBForeignKey::type() const
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
  return false;
}
