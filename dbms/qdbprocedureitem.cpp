#include "qdbprocedureitem.h"
#include "dbms/appconst.h"
#include <QIcon>

DBProcedureItem::DBProcedureItem(QString caption, QObject *parent):
  DBObjectItem(caption, parent)
{
  registerField(F_SOURCE_CODE);
  registerField(F_LANGUAGE);
  registerField(F_RETURN_TYPE);
}

DBProcedureItem::~DBProcedureItem()
{
}


int DBProcedureItem::colCount()
{
  return 1;
}

QVariant DBProcedureItem::colData(int column, int role)
{
  Q_UNUSED(column)

  switch (role) {
  case Qt::DisplayRole:
    return fieldValue(F_CAPTION);
  case Qt::DecorationRole:
    return QIcon(":/icons/function.png");
  default:
    return QVariant();
  }
}

bool DBProcedureItem::reloadChildren()
{
  return true;
}

int DBProcedureItem::type()
{
  return Procedure;
}
