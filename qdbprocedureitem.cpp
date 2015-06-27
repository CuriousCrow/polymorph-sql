#include "qdbprocedureitem.h"


QDBProcedureItem::QDBProcedureItem(QString caption, QObject *parent):
  QDBObjectItem(caption, parent)
{
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
  switch (role) {
  case Qt::DisplayRole:
    return caption();
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
