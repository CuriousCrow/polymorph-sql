#include "tableinfomodel.h"
#include <QDebug>


TableInfoModel::TableInfoModel(QObject *parent) : QAbstractTableModel(parent)
{
}

void TableInfoModel::addSqlColumn(SqlColumn col, bool init)
{
  emit beginInsertRows(QModelIndex(), _idxList.count(), _idxList.count());
  _idxList.append(col.name());
  if (init)
    _dataHash.insert(col.name(), col);
  else
    _changes.insert(col.name(), col);
  emit endInsertRows();
}

SqlColumn TableInfoModel::columnByIndex(int idx)
{
  QString colName = _idxList.at(idx);
  return _changes.contains(colName) ? _changes[colName] : _dataHash[colName];
}

int TableInfoModel::rowByName(const QString name)
{
  return _idxList.indexOf(name);
}

QHash<SqlColumn, SqlColumn> TableInfoModel::columnChanges()
{
    QHash<SqlColumn, SqlColumn> result;
    foreach (QString colName, _changes.keys()) {
        if (_idxList.contains(colName)) {
            //Modified column
            if (_dataHash.contains(colName)) {
                result.insert(_dataHash.value(colName), _changes.value(colName));
            }
            //New column
            else {
                result.insert(SqlColumn(colName, ColumnType::NoType), _changes.value(colName));
            }
        }
        //Removed column
        else {
            result.insert(_dataHash.value(colName), SqlColumn(colName, ColumnType::NoType));
        }
    }
    return result;
}

TableInfoModel::EditType TableInfoModel::editType()
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

void TableInfoModel::revertAll()
{
  emit beginResetModel();
  while (!_changes.isEmpty()) {
    QString name = _changes.keys().first();
    if (_idxList.contains(name)) {
      if (!_dataHash.contains(name)) {
        //Было добавление
        _idxList.removeOne(name);
      }
      else {
        //Было редактирование
      }
    }
    else {
      //Было удаление
      _dataHash.insert(name, _changes.value(name));
      _idxList.append(name);
    }
    _changes.remove(name);
  }
  emit endResetModel();
}

void TableInfoModel::clear()
{
    emit beginResetModel();
    _idxList.clear();
    _changes.clear();
    _dataHash.clear();
    emit endResetModel();
}

int TableInfoModel::rowCount(const QModelIndex &parent) const
{
  return _idxList.size();
}

int TableInfoModel::columnCount(const QModelIndex &parent) const
{
  return 7;
}

QVariant TableInfoModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();
  SqlColumn col;
  if (_changes.contains(_idxList.at(index.row())))
    col =_changes.value(_idxList.at(index.row()));
  else
    col = _dataHash.value(_idxList.at(index.row()));
  if (role == Qt::DisplayRole || role == Qt::EditRole) {
    switch (index.column()) {
    case 0:
      return col.isPrimary();
    case 1:
      return col.name();
    case 2:
      return columnTypeCaption(col.type());
    case 3:
      return col.length();
    case 4:
      return col.precision();
    case 5:
      return col.notNull();
    case 6:
      return col.defaultValue();
    default:
      return QVariant();
    }
  }
  return QVariant();
}

bool TableInfoModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (!index.isValid())
    return false;
  if (role == Qt::EditRole) {
    QString colName = _idxList.at(index.row());
    SqlColumn col;
    if (_changes.contains(colName))
      col = _changes[colName];
    else
      col = _dataHash[colName];
    switch (index.column()) {
    case 0:
      col.setIsPrimary(value.toBool());
      break;
    case 1:
      _dataHash[colName].setName(value.toString());
      col.setName(value.toString());
      break;
    case 2:
      col.setType((ColumnType)value.toInt());
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
    default:
      return false;
    }
    _changes.insert(colName, col);
    return true;
  }
  return true;
}

QVariant TableInfoModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  if (orientation == Qt::Horizontal) {
    switch (section) {
    case 0:
      return trUtf8("Primary key");
    case 1:
      return trUtf8("Column name");
    case 2:
      return trUtf8("Type");
    case 3:
      return trUtf8("Length");
    case 4:
      return trUtf8("Precision");
    case 5:
      return trUtf8("Not null");
    case 6:
      return trUtf8("Default value");
    default:
      return QVariant();
    }
  }
  else {
    return section;
  }
}

bool TableInfoModel::insertRows(int row, int count, const QModelIndex &parent)
{
  if (row < 0 || row > rowCount() || count != 1)
    return false;

  emit beginInsertRows(QModelIndex(), row, row);
  QString newColname = trUtf8("Column") + QString::number(rowCount() + 1);
  SqlColumn newCol(newColname, ColumnType::Integer);
  _idxList.insert(row, newColname);
  _changes.insert(newColname, newCol);
  emit endInsertRows();
  return true;
}

bool TableInfoModel::removeRows(int row, int count, const QModelIndex &parent)
{
  if (row < 0 || row >= rowCount() || count != 1)
    return false;

  emit beginRemoveRows(QModelIndex(), row, row);
  QString oldColname = _idxList.at(row);
  _idxList.removeAt(row);
  _changes.insert(oldColname, _dataHash.value(oldColname));
  emit endRemoveRows();
  return true;
}

Qt::ItemFlags TableInfoModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::NoItemFlags;
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

SqlColumn::SqlColumn()
{
  _type = NoType;
  //
  _precision = 0;
  _length = 0;
  _notNull = false;
  _isPrimary = false;
}

SqlColumn::SqlColumn(QString name, ColumnType type)
{
  _name = name;
  _type = type;
  //
  _precision = 0;
  _length = 0;
  _notNull = false;
  _isPrimary = false;
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
}

QString SqlColumn::name() const
{
  return _name;
}

void SqlColumn::setName(const QString &name)
{
  if (_name != name && _oldName.isEmpty()) {
    _oldName = _name;
  }
  _name = name;
}

QString SqlColumn::oldName()
{
  return _oldName;
}

ColumnType SqlColumn::type() const
{
  return _type;
}

void SqlColumn::setType(const ColumnType &type)
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

bool SqlColumn::operator ==(const SqlColumn &other)
{
    return (this->name() == other.name()) && (this->type() == other.type())
            && (this->length() == other.length()) && (this->isPrimary() == other.isPrimary())
            && (this->notNull() == other.notNull()) && (this->defaultValue() == other.defaultValue());
}

SqliteTableInfoModel::SqliteTableInfoModel(QObject *parent) : TableInfoModel(parent)
{
}

ColumnTypes SqliteTableInfoModel::supportedColumnTypes()
{
  return ColumnType::Varchar | ColumnType::Integer | ColumnType::Numeric | ColumnType::Blob;
}

QString SqliteTableInfoModel::columnTypeCaption(const ColumnType type) const
{
  switch (type) {
  case Varchar:
    return "TEXT";
  case Integer:
    return "INTEGER";
  case Numeric:
    return "REAL";
  case Blob:
    return "BLOB";
  default:
    //Другие типы не поддерживаются
    Q_ASSERT(false);
  }
}

QDebug operator<<(QDebug dbg, const SqlColumn &column)
{
    dbg.noquote().nospace() << "Column {name: " << column.name() << ", type:" << column.type()
                            << ", length: " << column.length() << ", notNull: " << column.notNull()
                            << ", defaultValue: " << column.defaultValue() << "}";
    return dbg;
}
