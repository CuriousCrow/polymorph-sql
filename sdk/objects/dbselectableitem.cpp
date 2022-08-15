#include "dbselectableitem.h"
#include <QIcon>
#include <QSqlDriver>
#include "objects/appconst.h"


DBSelectableItem::DBSelectableItem(QString caption, QObject *parent) : DBObjectItem(caption, parent)
{
  _identifierSupport = new QuoteIdentifier();
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

QString DBSelectableItem::fillSqlPatternWithFields(QString pattern) const
{
  QString sql = DBObjectItem::fillSqlPatternWithFields(pattern);
  return sql.replace("#identifier#", identifier());
}
