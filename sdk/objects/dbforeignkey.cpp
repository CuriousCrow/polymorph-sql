#include "dbforeignkey.h"
#include "appconst.h"
#include "utils/sqlqueryhelper.h"


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
  return execSql(toDDL(), connectionName());
}

QString DBForeignKey::toDDL() const
{
    QString sql = "alter table #table# add constraint #caption# "
                  "foreign key (#column#) references #reftable#(#refcolumn#) "
                  "on update #onUpdate# on delete #onDelete#";
    return fillSqlPatternWithFields(sql);
}


bool DBForeignKey::refresh()
{
  return false;
}

QString DBForeignKey::fillSqlPatternWithFields(QString pattern) const
{
  QString sql = pattern.replace("#reftable#", _identifierSupport->escapeIdentifier(fieldValue(F_REFTABLE).toString()));
  return DBConstraintItem::fillSqlPatternWithFields(sql);
}
