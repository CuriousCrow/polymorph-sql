#include "lsqlquerymodel.h"
#include <QSqlRecord>

LSqlQueryModel::LSqlQueryModel(QObject *parent): QAbstractTableModel(parent)
{  
}

void LSqlQueryModel::reload(QSqlQuery &query)
{
  beginResetModel();

  clear();

  if (query.isSelect() && query.isActive()) {
    bool headersDefined = false;
    while(query.next()) {
      if (!headersDefined) {
        updateHeaders(query.record());
        headersDefined = true;
      }
      QVariantList row;
      QSqlRecord rec = query.record();
      for(int col = 0; col < rec.count(); col++) {
        row.append(rec.value(col));
      }
      _rows.append(row);
    }
  }

  endResetModel();
}

int LSqlQueryModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return _rows.count();
}

int LSqlQueryModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return _headers.count();
}

QVariant LSqlQueryModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();
  if (role == Qt::DisplayRole) {
    return _rows.at(index.row()).at(index.column());
  }
  return QVariant();
}

void LSqlQueryModel::clear()
{
  _headers.clear();
  _rows.clear();
}

void LSqlQueryModel::updateHeaders(const QSqlRecord &rec)
{
  _headers.clear();

  for(int col = 0; col < rec.count(); col++) {
    _headers.append(rec.fieldName(col));
  }
}

QVariant LSqlQueryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role != Qt::DisplayRole)
    return QVariant();
  if (orientation == Qt::Vertical)
    return section;
  else {
    return _headers.at(section);
  }
}
