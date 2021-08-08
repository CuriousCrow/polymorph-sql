#include "sqlcolumnmodel.h"
#include <QDebug>

SqlColumnModel::SqlColumnModel(QObject *parent) : QAbstractTableModel(parent)
{

}

QString SqlColumnModel::columnTypeCaption(int type) const
{
  return _kb->typeName(type);
}

void SqlColumnModel::addSqlColumn(SqlColumn col, bool init)
{
  emit beginInsertRows(QModelIndex(), _idxList.count(), _idxList.count());
  qlonglong newId = getNextId();
  _idxList.append(newId);
  if (init)
    _dataHash.insert(newId, col);
  else
    _changes.insert(newId, col);
  emit endInsertRows();
}

SqlColumn SqlColumnModel::columnByIndex(int idx)
{
  qlonglong colId = _idxList.at(idx);
  return _changes.contains(colId) ? _changes[colId] : _dataHash[colId];
}

int SqlColumnModel::rowByName(const QString name)
{
  qlonglong resId = 0;
  foreach (qlonglong id, _changes.keys()) {
    if (_changes.value(id).name() == name) {
      return _idxList.indexOf(id);
    }
  }
  if (resId > 0)
    return _idxList.indexOf(resId);
  foreach (qlonglong id, _dataHash.keys()) {
    if (_dataHash.value(id).name() == name) {
      return _idxList.indexOf(id);
    }
  }
  return -1;
}

QHash<SqlColumn, SqlColumn> SqlColumnModel::columnChanges()
{
  QHash<SqlColumn, SqlColumn> result;
  foreach (qlonglong colId, _changes.keys()) {
    if (_idxList.contains(colId)) {
      //Modified column
      if (_dataHash.contains(colId)) {
        result.insert(_dataHash.value(colId), _changes.value(colId));
      }
      //New column
      else {
        result.insert(SqlColumn("Empty_" + QString::number(colId), 0), _changes.value(colId));
      }
    }
    //Removed column
    else {
      result.insert(_dataHash.value(colId), SqlColumn("", 0));
    }
  }
  return result;
}

QHash<QString, QString> SqlColumnModel::permanentColNames()
{
  QHash<QString, QString> resHash;
  foreach (qlonglong colId, _dataHash.keys()) {
    if (_idxList.contains(colId)) {
      if (_changes.contains(colId)) {
        resHash.insert(_dataHash.value(colId).name(), _changes.value(colId).name());
      }
      else {
        resHash.insert(_dataHash.value(colId).name(), _dataHash.value(colId).name());
      }
    }
  }
  return resHash;
}

SqlColumnModel::EditType SqlColumnModel::editType()
{
  if (_changes.isEmpty()) {
    return EditType::NoChanges;
  }
  else if (_idxList.isEmpty()) {
    return EditType::DropTable;
  }
  else if (_dataHash.isEmpty()) {
    return EditType::CreateTable;
  }
  else {
    return EditType::ModifyTable;
  }
}

bool SqlColumnModel::hasOnlyIntegerPK()
{
//        //TODO: Надо разобраться
//  int pkCount = 0;
//  int intPkCount = 0;
//  for(int i=0; i<rowCount(); i++) {
//    SqlColumn col = columnByIndex(i);
//    if (col.isPrimary()) {
//      if (col.type() == ColumnType::Integer)
//        intPkCount++;
//      pkCount++;
//    }
//  }
//  return (pkCount == 1) && (intPkCount == 1);
  return true;
}

bool SqlColumnModel::isModified()
{
  return !_changes.isEmpty();
}

void SqlColumnModel::clear()
{
  emit beginResetModel();
  _idxList.clear();
  _changes.clear();
  _dataHash.clear();
  emit endResetModel();
}

int SqlColumnModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return _idxList.count();
}

int SqlColumnModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return 8;
}

QVariant SqlColumnModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();
  bool modified = false;
  SqlColumn col;
  if (_changes.contains(_idxList.at(index.row()))) {
    col =_changes.value(_idxList.at(index.row()));
    SqlColumn oldCol = _dataHash.value(_idxList.at(index.row()));
    if (oldCol.type() == NoType) {
      modified = true;
    }
    else {
      if (oldCol.valueByIndex(index.column()) != col.valueByIndex(index.column()))
        modified = true;
    }
  }
  else
    col = _dataHash.value(_idxList.at(index.row()));
  if (role == Qt::DisplayRole || role == Qt::EditRole) {
    QVariant resVal = col.valueByIndex(index.column());
    if (index.column() == COL_IDX_TYPE)
      resVal = columnTypeCaption(resVal.toInt());
    return resVal;
  }
  else if (role == Qt::BackgroundRole) {
    if (modified) {
      return _modifiedColor;
    }
    return QVariant();
  }
  return QVariant();
}

bool SqlColumnModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (!index.isValid())
    return false;
  if (role == Qt::EditRole) {
    qlonglong colId = _idxList.at(index.row());
    SqlColumn col;
    if (_changes.contains(colId))
      col = _changes[colId];
    else
      col = _dataHash[colId];
    switch (index.column()) {
    case 0:
      col.setIsPrimary(value.toBool());
      break;
    case 1:
      col.setName(value.toString());
      break;
    case 2:
      col.setType(value.toInt());
      break;
    case 3:
      col.setLength(value.toInt());
      break;
    case 4:
      col.setPrecision(value.toInt());
      break;
    case 5:
      col.setNotNull(value.toBool());
      break;
    case 6:
      col.setDefaultValue(value);
      break;
    case 7:
      col.setAutoIncrement(value.toBool());
      break;
    default:
      return false;
    }
    _changes.insert(colId, col);
    return true;
  }
  return true;
}

QVariant SqlColumnModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  if (orientation == Qt::Horizontal) {
    switch (section) {
    case 0:
      return tr("Primary key");
    case 1:
      return tr("Column name");
    case 2:
      return tr("Type");
    case 3:
      return tr("Length");
    case 4:
      return tr("Precision");
    case 5:
      return tr("Not null");
    case 6:
      return tr("Default value");
    case 7:
      return tr("Autoincrement");
    default:
      return QVariant();
    }
  }
  else {
    return section;
  }
}

bool SqlColumnModel::insertRows(int row, int count, const QModelIndex &parent)
{
  Q_UNUSED(parent)
  if (row < 0 || row > rowCount() || count != 1)
    return false;

  emit beginInsertRows(QModelIndex(), row, row);
  QString newColname = tr("Column") + QString::number(rowCount() + 1);
  SqlColumn newCol(newColname, NoType);
  qlonglong newId = getNextId();
  _idxList.insert(row, newId);
  _changes.insert(newId, newCol);
  emit endInsertRows();
  return true;
}

bool SqlColumnModel::removeRows(int row, int count, const QModelIndex &parent)
{
  Q_UNUSED(parent)
  if (row < 0 || row >= rowCount() || count != 1)
    return false;

  emit beginRemoveRows(QModelIndex(), row, row);
  qlonglong idToRemove = _idxList.at(row);
  _idxList.removeAt(row);
  _changes.insert(idToRemove, _dataHash[idToRemove]);
  emit endRemoveRows();
  return true;
}

Qt::ItemFlags SqlColumnModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::NoItemFlags;
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

qlonglong SqlColumnModel::getNextId()
{
  return ++_idGen;
}

SqlColumn::SqlColumn()
{
  _type = NoType;
  //
  _precision = 0;
  _length = 0;
  _notNull = false;
  _isPrimary = false;
  _autoIncrement = false;
}

SqlColumn::SqlColumn(QString name, int type)
{
  _name = name;
  _type = type;
  //
  _precision = 0;
  _length = 0;
  _notNull = false;
  _isPrimary = false;
  _autoIncrement = false;
}

SqlColumn::SqlColumn(const SqlColumn &other)
{
  this->_name = other.name();
  this->_type = other.type();
  this->_length = other.length();
  this->_precision = other.precision();
  this->_isPrimary = other.isPrimary();
  this->_notNull = other.notNull();
  this->_defaultValue = other.defaultValue();
  this->_autoIncrement = other.autoIncrement();
}

QString SqlColumn::name() const
{
  return _name;
}

void SqlColumn::setName(const QString &name)
{
  _name = name;
}

int SqlColumn::type() const
{
  return _type;
}

void SqlColumn::setType(const int &type)
{
  _type = type;
}

int SqlColumn::length() const
{
  return _length;
}

void SqlColumn::setLength(int length)
{
  _length = length;
}

int SqlColumn::precision() const
{
  return _precision;
}

void SqlColumn::setPrecision(int precision)
{
  _precision = precision;
}

bool SqlColumn::notNull() const
{
  return _notNull;
}

void SqlColumn::setNotNull(bool notNull)
{
  _notNull = notNull;
}

bool SqlColumn::isPrimary() const
{
  return _isPrimary;
}

void SqlColumn::setIsPrimary(bool isPrimary)
{
  _isPrimary = isPrimary;
}

QVariant SqlColumn::defaultValue() const
{
  return _defaultValue;
}

void SqlColumn::setDefaultValue(const QVariant &defaultValue)
{
  _defaultValue = defaultValue;
}

bool SqlColumn::autoIncrement() const
{
  return _autoIncrement;
}

void SqlColumn::setAutoIncrement(bool autoIncrement)
{
  _autoIncrement = autoIncrement;
}

QVariant SqlColumn::valueByIndex(int idx)
{
  switch (idx) {
  case 0:
    return this->isPrimary();
  case 1:
    return this->name();
  case 2:
    return this->type();
  case 3:
    return this->length();
  case 4:
    return this->precision();
  case 5:
    return this->notNull();
  case 6:
    return this->defaultValue();
  case 7:
    return this->autoIncrement();
  default:
    return QVariant();
  }
}

bool SqlColumn::operator ==(const SqlColumn &other)
{
  return (this->name() == other.name()) && (this->type() == other.type())
      && (this->length() == other.length()) && (this->isPrimary() == other.isPrimary())
      && (this->notNull() == other.notNull()) && (this->defaultValue() == other.defaultValue())
      && (this->autoIncrement() == other.autoIncrement());
}

QDebug operator<<(QDebug dbg, const SqlColumn &column)
{
  dbg.noquote().nospace() << "Column {name: " << column.name() << ", type:" << column.type()
                          << ", length: " << column.length() << ", notNull: " << column.notNull()
                          << ", defaultValue: " << column.defaultValue() << ", autoIncrement: " << column.autoIncrement() + "}";
  return dbg;
}
