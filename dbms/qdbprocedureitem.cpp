#include "qdbprocedureitem.h"
#include "dbms/appconst.h"
#include <QIcon>

QDBProcedureItem::QDBProcedureItem(QString caption, QUrl url, QObject *parent):
  QDBObjectItem(caption, url, parent)
{
  registerField(F_SOURCE_CODE);
  registerField(F_LANGUAGE);
  registerField(F_RETURN_TYPE);
}

QDBProcedureItem::~QDBProcedureItem()
{
}


int QDBProcedureItem::colCount()
{
  return 1;
}

QVariant QDBProcedureItem::colData(int column, int role)
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

bool QDBProcedureItem::loadChildren()
{
  return true;
}

int QDBProcedureItem::type()
{
  return Procedure;
}
