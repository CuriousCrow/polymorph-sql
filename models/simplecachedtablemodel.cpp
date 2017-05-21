#include "simplecachedtablemodel.h"

SimpleCachedTableModel::SimpleCachedTableModel(CacheRowObject sampleRow, QObject *parent)
  : QAbstractTableModel(parent)
{
  _sampleRowObj = sampleRow;
}

void SimpleCachedTableModel::addRow(CacheRowObject *rowObj)
{

}

int SimpleCachedTableModel::rowCount(const QModelIndex &parent) const
{
  return _rows.count();
}

int SimpleCachedTableModel::columnCount(const QModelIndex &parent) const
{
  return _sampleRowObj.count();
}

QVariant SimpleCachedTableModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();
  if (role == Qt::DisplayRole) {
    return _rows.at(index.row())->fieldValue(index.column());
  }
  return QVariant();
}

bool SimpleCachedTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  switch (role) {
  case Qt::EditRole:
    _rows.at(index.row())->setValue(index.column(), value);
    return true;
  default:
    break;
  }
  return false;
}

QVariant SimpleCachedTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Horizontal) {
    return _sampleRowObj.field(section)->name();
  }
  return QVariant();
}

Qt::ItemFlags SimpleCachedTableModel::flags(const QModelIndex &index) const
{
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

bool SimpleCachedTableModel::submit()
{
//
}

void SimpleCachedTableModel::revert()
{
//
}

CacheField::CacheField(QString name, QVariant initValue)
{
  _name = name;
  _oldValue = initValue;
  _value = initValue;
  _modified = false;
}

QString CacheField::name()
{
  return _name;
}

void CacheField::setValue(QVariant val)
{
  if (_value != val) {
    _oldValue = _value;
    _value = val;
    _modified = true;
  }
}

QVariant CacheField::value()
{
  return _value;
}

QVariant CacheField::oldValue()
{
  return _oldValue;
}

void CacheField::revert()
{
  _value = _oldValue;
  _modified = false;
}

CacheRowObject::CacheRowObject()
{
}

QVariant CacheRowObject::fieldValue(int idx)
{
  return _fields.at(idx)->value();
}

QVariant CacheRowObject::fieldValue(QString field)
{
  return fieldValue(fieldIdxByName(field));
}

void CacheRowObject::setValue(int idx, QVariant val)
{
  return _fields.at(idx)->setValue(val);
}

void CacheRowObject::setValue(QString field, QVariant val)
{
  return setValue(fieldIdxByName(field), val);
}

int CacheRowObject::count() const
{
  return _fields.count();
}

CacheField *CacheRowObject::field(int idx) const
{
  return _fields.at(idx);
}

void CacheRowObject::registerField(CacheField *field)
{
  _fields.append(field);
}

int CacheRowObject::fieldIdxByName(QString field)
{
  for(int idx; idx < _fields.count(); idx++) {
    if (_fields.at(idx)->name() == field)
      return idx;
  }
  return -1;
}
