#include "qdbsequenceitem.h"


QDBSequenceItem::QDBSequenceItem(QString caption, QObject *parent):
  QDBObjectItem(caption, parent)
{
}

QDBSequenceItem::~QDBSequenceItem()
{
}

int QDBSequenceItem::colCount()
{
  return 1;
}

QVariant QDBSequenceItem::colData(int column, int role)
{
  Q_UNUSED(column)

  switch (role) {
  case Qt::DisplayRole:
    return fieldValue("caption");
  default:
    return QVariant();
  }
}

bool QDBSequenceItem::loadChildren()
{
  return true;
}

int QDBSequenceItem::type()
{
  return Sequence;
}
