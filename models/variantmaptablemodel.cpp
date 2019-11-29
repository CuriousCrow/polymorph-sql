#include "variantmaptablemodel.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>


VariantMapTableModel::VariantMapTableModel(QObject *parent) : QAbstractTableModel(parent)
{

}

void VariantMapTableModel::registerColumn(AbstractColumn *column)
{
  _columns.append(column);
}

void VariantMapTableModel::registerColumn(QString name, QString caption)
{
  registerColumn(new SimpleColumn(name, caption));
}

void VariantMapTableModel::addRow(QVariantMap rowData)
{
    int id = rowData.value("id").toInt();
    beginInsertRows(QModelIndex(), _rowIndex.count(), _rowIndex.count());
    _rowIndex.append(id);
    _dataHash.insert(id, rowData);
    endInsertRows();
}

void VariantMapTableModel::deleteByRow(int row)
{
  beginRemoveRows(QModelIndex(), row, row);
  int id = idByRow(row);
  _rowIndex.removeAt(row);
  _dataHash.remove(id);
  endRemoveRows();
}

void VariantMapTableModel::clear()
{
  beginResetModel();
  _rowIndex.clear();
  _dataHash.clear();
  endResetModel();
}

QVariant VariantMapTableModel::data(int row, QString colName)
{
  int id = idByRow(row);
  QVariantMap rowData = _dataHash.value(id);
  return rowData.value(colName);
}

int VariantMapTableModel::idByRow(int row) const
{
    return _rowIndex.at(row);
}

int VariantMapTableModel::rowById(int id) const
{
    return _rowIndex.indexOf(id);
}

int VariantMapTableModel::colByName(QString name) const
{
    for(int col = 0; col < _columns.count(); col++) {
        if (nameByCol(col) == name)
            return col;
    }
    return -1;
}

QString VariantMapTableModel::nameByCol(int col) const
{
    return _columns.at(col)->name();
}

int VariantMapTableModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return _rowIndex.count();
}

int VariantMapTableModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return _columns.count();
}

QVariant VariantMapTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    int id = idByRow(index.row());
    QVariantMap rowData = _dataHash.value(id);
    return _columns.at(index.column())->colData(rowData, role);
}


SimpleColumn::SimpleColumn(QString name, QString caption) : AbstractColumn(name, caption)
{
}

QVariant SimpleColumn::colData(const QVariantMap &rowData, int role)
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return rowData.value(name());

    return QVariant();
}

AbstractColumn::AbstractColumn(QString name, QString caption) :
  _name(name), _caption(caption.isEmpty() ? name : caption)
{
}

AbstractColumn::~AbstractColumn()
{
}


bool VariantMapTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    if (role == Qt::EditRole) {
        int id = idByRow(index.row());
        _dataHash[id].insert(nameByCol(index.column()), value);
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags VariantMapTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

LookupColumn::LookupColumn(QString name, VariantMapTableModel *model, QString keyCol, QString lookupCol)
    : AbstractColumn(name), _lookupModel(model), _keyColumn(keyCol), _lookupColumn(lookupCol)
{

}

QVariant LookupColumn::colData(const QVariantMap &rowData, int role)
{
    if (role == Qt::DisplayRole) {
        int key = rowData.value(_keyColumn).toInt();
        int lookupRow = _lookupModel->rowById(key);
        if (lookupRow < 0)
            return QVariant();
        int lookupCol = _lookupModel->colByName(_lookupColumn);
        return _lookupModel->index(lookupRow, lookupCol).data();
    }
    return QVariant();
}

QVariant VariantMapTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
    return _columns.at(section)->caption();
  }
  return QAbstractTableModel::headerData(section, orientation, role);
}
