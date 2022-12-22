#include "sqlcolumnmodel.h"
#include <QDebug>
#include "objects/appconst.h"

SqlColumnModel::SqlColumnModel(QObject *parent) : QAbstractTableModel(parent)
{
  connect(this, &SqlColumnModel::dataChanged, this, &SqlColumnModel::onDataChanged);
}

void SqlColumnModel::setTypeProvider(TypeProvider *provider)
{
  _typeProvider = provider;
}

void SqlColumnModel::addSqlColumn(SqlColumn col, bool init)
{
  beginInsertRows(QModelIndex(), _idxList.count(), _idxList.count());
  qlonglong newId = getNextId();
  _idxList.append(newId);
  if (init)
    _dataHash.insert(newId, col);
  else
    _changes.insert(newId, col);
  endInsertRows();
}

SqlColumn SqlColumnModel::columnByIndex(int idx)
{
  qlonglong colId = _idxList.at(idx);
  return _changes.contains(colId) ? _changes[colId] : _dataHash[colId];
}

int SqlColumnModel::rowByName(const QString name)
{
  qlonglong resId = 0;
  QHashIterator<qlonglong, SqlColumn> i(_changes);
  while(i.hasNext()) {
    i.next();
    if (i.value().name() == name) {
      return _idxList.indexOf(i.key());
    }
  }
  if (resId > 0)
    return _idxList.indexOf(resId);
  QHashIterator<qlonglong, SqlColumn> it(_dataHash);
  while(it.hasNext()) {
    it.next();
    if (it.value().name() == name) {
      return _idxList.indexOf(it.key());
    }
  }
  return -1;
}

QHash<SqlColumn, SqlColumn> SqlColumnModel::columnChanges()
{
  QHash<SqlColumn, SqlColumn> result;
  QHashIterator<qlonglong, SqlColumn> it(_changes);
  while(it.hasNext()) {
    it.next();
    if (_idxList.contains(it.key())) {
      //Modified column
      if (_dataHash.contains(it.key())) {
        result.insert(_dataHash.value(it.key()), it.value());
      }
      //New column
      else {
        result.insert(SqlColumn("Empty_" + QString::number(it.key()), 0), it.value());
      }
    }
    //Removed column
    else {
      result.insert(_dataHash.value(it.key()), SqlColumn("", 0));
    }
  }
  return result;
}

QHash<QString, QString> SqlColumnModel::permanentColNames()
{
  QHash<QString, QString> resHash;
  QHashIterator<qlonglong, SqlColumn> it(_dataHash);
  while(it.hasNext()) {
    it.next();
    if (_idxList.contains(it.key())) {
      if (_changes.contains(it.key())) {
        resHash.insert(it.value().name(), _changes.value(it.key()).name());
      }
      else {
        resHash.insert(it.value().name(), it.value().name());
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

bool SqlColumnModel::hasOneColumnPK()
{
  int pkCount = 0;
  for(int i=0; i<rowCount(); i++) {
    SqlColumn col = columnByIndex(i);
    if (col.isPrimary()) {
      pkCount++;
    }
  }
  return (pkCount == 1);
}

bool SqlColumnModel::isModified()
{
  return !_changes.isEmpty();
}

void SqlColumnModel::clear()
{
  beginResetModel();
  _idxList.clear();
  _changes.clear();
  _dataHash.clear();
  endResetModel();
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
    case COL_IDX_PK:
      col.setIsPrimary(value.toBool());
      break;
    case COL_IDX_NAME:
      col.setName(value.toString());
      break;
    case COL_IDX_TYPE:
      col.setType(value.toString());
      break;
    case COL_IDX_LENGTH:
      col.setLength(value.toInt());
      break;
    case COL_IDX_PRECISION:
      col.setPrecision(value.toInt());
      break;
    case COL_IDX_NOTNULL:
      col.setNotNull(value.toBool());
      break;
    case COL_IDX_DEFAULT:
      col.setDefaultValue(value);
      break;
    case COL_IDX_AUTOINCREMENT:
      col.setAutoIncrement(value.toBool());
      break;
    default:
      return false;
    }
    _changes.insert(colId, col);
    emit dataChanged(index, index);
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
    case COL_IDX_PK:
      return tr("Primary key");
    case COL_IDX_NAME:
      return tr("Column name");
    case COL_IDX_TYPE:
      return tr("Type");
    case COL_IDX_LENGTH:
      return tr("Length");
    case COL_IDX_PRECISION:
      return tr("Precision");
    case COL_IDX_NOTNULL:
      return tr("Not null");
    case COL_IDX_DEFAULT:
      return tr("Default value");
    case COL_IDX_AUTOINCREMENT:
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

  beginInsertRows(QModelIndex(), row, row);
  QString newColname = tr("Column") + QString::number(rowCount() + 1);
  SqlColumn newCol(newColname, NoType);
  qlonglong newId = getNextId();
  _idxList.insert(row, newId);
  _changes.insert(newId, newCol);
  endInsertRows();
  return true;
}

bool SqlColumnModel::removeRows(int row, int count, const QModelIndex &parent)
{
  Q_UNUSED(parent)
  if (row < 0 || row >= rowCount() || count != 1)
    return false;

  beginRemoveRows(QModelIndex(), row, row);
  qlonglong idToRemove = _idxList.at(row);
  _idxList.removeAt(row);
  _changes.insert(idToRemove, _dataHash[idToRemove]);
  endRemoveRows();
  return true;
}

Qt::ItemFlags SqlColumnModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::NoItemFlags;
  if (index.column() == COL_IDX_LENGTH && !hasLength(index.row())) {
    return Qt::NoItemFlags;
  }
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

qlonglong SqlColumnModel::getNextId()
{
  return ++_idGen;
}

void SqlColumnModel::onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
  Q_UNUSED(bottomRight)
  Q_UNUSED(roles)

  if (topLeft.column() == COL_IDX_TYPE) {
    if (!hasLength(topLeft.row()))
      setData(index(topLeft.row(), COL_IDX_LENGTH), QVariant(), Qt::EditRole);
  }
}

bool SqlColumnModel::hasLength(int row) const
{
  QString typeName = index(row, COL_IDX_TYPE).data().toString();
  DBType* type = _typeProvider->type(typeName);
  if (!type)
    return false;
  return type->hasLength();
}

SqlColumn::SqlColumn()
{
  setName("");
  setType(NoType);
  setDefaultValue(QVariant());
  setLength(0);
  setPrecision(0);
  setNotNull(false);
  setIsPrimary(false);
  setAutoIncrement(false);
}

SqlColumn::SqlColumn(QString name, QString type) : SqlColumn()
{
  setName(name);
  setType(type);
}

SqlColumn::SqlColumn(const SqlColumn &other)
{
  setName(other.name());
  setType(other.type());
  setPrecision(other.precision());
  setLength(other.length());
  setNotNull(other.notNull());
  setIsPrimary(other.isPrimary());
  setAutoIncrement(other.autoIncrement());
}

QString SqlColumn::name() const
{
  return _colData.value(PRM_NAME).toString();
}

void SqlColumn::setName(const QString &name)
{
  _colData.insert(F_NAME, name);
}

QString SqlColumn::type() const
{
  return _colData.value(F_TYPE).toString();
}

void SqlColumn::setType(const QString &type)
{
  _colData.insert(F_TYPE, type);
}

int SqlColumn::length() const
{
  return _colData.value(F_LENGTH).toInt();
}

void SqlColumn::setLength(int length)
{
  _colData.insert(F_LENGTH, length);
}

int SqlColumn::precision() const
{
  return _colData.value(F_PRECISION).toInt();
}

void SqlColumn::setPrecision(int precision)
{
  _colData.insert(F_PRECISION, precision);
}

bool SqlColumn::notNull() const
{
  return _colData.value(F_NOT_NULL).toBool();
}

void SqlColumn::setNotNull(bool notNull)
{
  _colData.insert(F_NOT_NULL, notNull);
}

bool SqlColumn::isPrimary() const
{
  return _colData.value(F_IS_PRIMARY).toBool();
}

void SqlColumn::setIsPrimary(bool isPrimary)
{
  _colData.insert(F_IS_PRIMARY, isPrimary);
}

QVariant SqlColumn::defaultValue() const
{
  return _colData.value(F_DEFAULT);
}

void SqlColumn::setDefaultValue(const QVariant &defaultValue)
{
  _colData.insert(F_DEFAULT, defaultValue);
}

bool SqlColumn::autoIncrement() const
{
  return _colData.value(F_AUTOINCREMENT).toBool();
}

void SqlColumn::setAutoIncrement(bool autoIncrement)
{
  _colData.insert(F_AUTOINCREMENT, autoIncrement);
}

QVariant SqlColumn::valueByIndex(int idx)
{
  switch (idx) {
  case COL_IDX_PK:
    return this->isPrimary();
  case COL_IDX_NAME:
    return this->name();
  case COL_IDX_TYPE:
    return this->type();
  case COL_IDX_LENGTH:
    return this->length() == 0 ? QVariant() : this->length();
  case COL_IDX_PRECISION:
    return this->precision() == 0 ? QVariant() : this->precision();
  case COL_IDX_NOTNULL:
    return this->notNull();
  case COL_IDX_DEFAULT:
    return this->defaultValue();
  case COL_IDX_AUTOINCREMENT:
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
