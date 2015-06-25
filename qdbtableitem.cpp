#include "qdbtableitem.h"
#include <QUrl>
#include <QIcon>

QDBTableItem::QDBTableItem(QString caption, QObject* parent):
  QDBObjectItem(caption, parent)
{  
}

QDBTableItem::~QDBTableItem()
{
}

bool QDBTableItem::loadChildren()
{
  return true;
}


QUrl QDBTableItem::objectUrl()
{
  QUrl url = QDBObjectItem::objectUrl();
  url.setPath("/" + caption());
  return url;
}


int QDBTableItem::colCount()
{
  return 1;
}

QVariant QDBTableItem::colData(int column, int role)
{
  switch (role) {
  case Qt::DisplayRole:
    switch (column) {
    case 0:
      return caption();
    default:
      return QVariant();
    }
  case Qt::DecorationRole:
    return QIcon(":/icons/table.png");
  default:
    return QVariant();
  }
}


int QDBTableItem::type()
{
  return Table;
}
