#include "tablerowmodel.h"
#include "qsqlqueryhelper.h"
#include <QSqlField>

TableRowModel::TableRowModel(QObject *parent) : QAbstractTableModel(parent)
{
}

void TableRowModel::setTableItem(QDBObjectItem *item)
{
  _tableItem = item;
  beginResetModel();
  _infoRec = QSqlQueryHelper::tableRowInfo(item->fieldValue("caption").toString(),
                                                     item->connectionName());\
  endResetModel();
}

int TableRowModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return _infoRec.count();
}

int TableRowModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return 5;
}

QVariant TableRowModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();
  if (role == Qt::DisplayRole || role == Qt::EditRole) {
    QSqlField field = _infoRec.field(index.row());
    switch (index.column()) {
    case 0:
      return field.name();
    case 1:
      return field.length();
    case 2:
      return field.requiredStatus() == 0;
    case 3:
      return field.name().compare("ID", Qt::CaseInsensitive) == 0;
    case 4:
      return false;
    default:
      break;
    }
  }
  return QVariant();
}

bool TableRowModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  Q_UNUSED(index)
  Q_UNUSED(value)
  Q_UNUSED(role)
  return true;
}

QVariant TableRowModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Horizontal) {
    if (role == Qt::DisplayRole) {
      switch (section) {
      case 0:
        return tr("Column");
      case 1:
        return tr("Size");
      case 2:
        return tr("Null");
      case 3:
        return tr("PK");
      case 4:
        return tr("Unique");
      default:
        return QVariant();
      }
    }
  }
  return QVariant();
}

QDBFieldItem::QDBFieldItem(QString caption, QObject *parent)
  : QDBObjectItem(caption, parent)
{
  registerField("size");
  registerField("null");
  registerField("pk");
  registerField("unique");
}
