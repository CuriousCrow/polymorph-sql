#include "dbselectableitem.h"
#include <QIcon>
#include <QSqlDriver>


DBSelectableItem::DBSelectableItem(QString caption, QObject *parent) : DBObjectItem(caption, parent)
{

}

int DBSelectableItem::colCount() const
{
    return 1;
}

QVariant DBSelectableItem::colData(int column, int role) const
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

bool DBSelectableItem::reloadChildren()
{
    return true;
}

QString DBSelectableItem::identifier() const
{
   QString objName = QSqlDatabase::database(connectionName()).driver()->escapeIdentifier(caption(), QSqlDriver::TableName);
    return objName;
}
