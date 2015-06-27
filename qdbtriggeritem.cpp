#include "qdbtriggeritem.h"


QDBTriggerItem::QDBTriggerItem(QString caption, QObject *parent):
  QDBObjectItem(caption, parent)
{
}

QDBTriggerItem::~QDBTriggerItem()
{
}


int QDBTriggerItem::colCount()
{
  return 1;
}

QVariant QDBTriggerItem::colData(int column, int role)
{
  switch (role) {
  case Qt::DisplayRole:
    return caption();
  default:
    return QVariant();
  }
}

bool QDBTriggerItem::loadChildren()
{
  return true;
}

int QDBTriggerItem::type()
{
  return Trigger;
}
