#include "qdbforeignkey.h"
#include "appconst.h"


QDBForeignKey::QDBForeignKey(QString caption, QObject *parent)
  : QDBConstraintItem(caption, parent)
{
  registerField(F_REFTABLE);
  registerField(F_REFCOLUMN);
  registerField(F_ON_UPDATE);
  registerField(F_ON_DELETE);
}

int QDBForeignKey::type()
{
  return QDBObjectItem::ForeignKey;
}

ActionResult QDBForeignKey::insertMe()
{
  QString sql = "alter table #table# add constraint #caption# "
                "foreign key (#column#) references #reftable#(#refcolumn#) "
                "on update #onUpdate# on delete #onDelete#";
  QString preparedSql = fillPatternWithFields(sql);
  return execSql(preparedSql, connectionName());
}
