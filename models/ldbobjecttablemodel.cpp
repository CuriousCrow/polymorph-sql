#include "ldbobjecttablemodel.h"
#include "../qsqlqueryhelper.h"
#include <QSqlRecord>


LDBObjectTableModel::LDBObjectTableModel(QObject *parent)
  : QAbstractTableModel(parent)
{
}

void LDBObjectTableModel::setFixedValue(QString name, QVariant value)
{
  _fixedValues.insert(name, value);
}

QVariant LDBObjectTableModel::fixedValue(QString name)
{
  return _fixedValues.value(name);
}

void LDBObjectTableModel::registerColumn(QString name)
{
  _columns.append(name);
}

void LDBObjectTableModel::setQuery(QString sql)
{
  _sqlQuery = sql;
}

void LDBObjectTableModel::reload(QString connectionName)
{
  beginResetModel();
  QSqlQuery result = QSqlQueryHelper::execSql(_sqlQuery, connectionName);
  while(result.next()) {
    QVariantMap rowData = _fixedValues;
    QSqlRecord rec = result.record();
    for(int idx=0; idx<rec.count(); idx++) {
      rowData.insert(rec.fieldName(idx), rec.value(idx));
    }
    QString name = rowData.value(_idxField).toString();
    _rowIndex.append(name);
    _dataMap.insert(name, rowData);
  }
  endResetModel();
}

int LDBObjectTableModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return _rowIndex.count();
}

int LDBObjectTableModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return _columns.count();
}

QVariant LDBObjectTableModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();
  if (role == Qt::DisplayRole || role == Qt::EditRole) {
    QString name = nameByRow(index.row());
    QVariantMap rowData = rowByName(name);
    return rowData.value(columnName(index.column()));
  }
  return QVariant();
}

QString LDBObjectTableModel::nameByRow(int row) const
{
  return _rowIndex.at(row);
}

QVariantMap LDBObjectTableModel::rowByName(QString name) const
{
  return _dataMap.value(name);
}

bool LDBObjectTableModel::contains(QString name) const
{
  return _dataMap.contains(name);
}

int LDBObjectTableModel::colByName(QString name) const
{
  return _columns.indexOf(name);
}

QString LDBObjectTableModel::columnName(int idx) const
{
  return _columns.at(idx);
}
