#include "unisqltablemodel.h"
#include <QSqlDriver>
#include <QDebug>
#include <QSqlError>
#include <QSqlResult>
#include <QColor>
#include "utils/sqlutils.h"

UniSqlTableModel::UniSqlTableModel(QObject *parent, QString connectionName)
  : QAbstractTableModel(parent)
{
  _connectionName = connectionName;
  _filterManager = new SqlFilterManager(this);
  connect(_filterManager, &SqlFilterManager::filterChanged,
          this, &UniSqlTableModel::select);
}

bool UniSqlTableModel::setTable(QString tableName)
{
  _tableName = tableName;
  QSqlDatabase conn = db();
  QString preparedName = conn.driver()->escapeIdentifier(_tableName, QSqlDriver::TableName);
  _patternRec = conn.record(preparedName);
  qDebug() << "setTable():" << _patternRec;
  _primaryKey = conn.primaryIndex(preparedName);
  if (_primaryKey.count() == 1 && _primaryKey.field(0).typeID() == QMetaType::Int) {
    _intPkField = _primaryKey.fieldName(0);
  }
  else {
    _intPkField = "";
  }
  return true;
}

bool UniSqlTableModel::execDDL(const QString &sql)
{
  return !execDML(sql).lastError().isValid();
}

QSqlQuery UniSqlTableModel::execDML(const QString &sql)
{
  QSqlQuery result(sql, db());
  qDebug() << QString("UniSqlTableModel::execQuery: %1").arg(sql);
  if (result.lastError().isValid()){
    QString errorMessage = result.lastError().databaseText();
    _sqlErrors.append(errorMessage);
    qDebug() << "UniSqlTableModel::sqlError: " << errorMessage;
  }
  return result;
}

void UniSqlTableModel::clearData()
{
  _genId = 1;
  _tempId = -1;
  _rowIndex.clear();
  _dataHash.clear();
  _changesHash.clear();
}

bool UniSqlTableModel::intPk()
{
  return !_intPkField.isEmpty();
}

bool UniSqlTableModel::noPk()
{
  return _primaryKey.isEmpty();
}

bool UniSqlTableModel::supportsReturning()
{
  QStringList list;
  list << "QIBASE" << "QPSQL";
  return list.contains(db().driverName());
}

qlonglong UniSqlTableModel::getId(QSqlQuery &query)
{
  if (!intPk()) {
    return genId();
  }
  else {
    return query.value(_intPkField).toLongLong();
  }
}

qlonglong UniSqlTableModel::genId()
{
  qDebug() << "Fake id generated:" << _genId;
  return _genId++;
}

qlonglong UniSqlTableModel::genTempId()
{
  qDebug() << "Temp id generated:" << _tempId;
  return _tempId--;
}

QSqlRecord UniSqlTableModel::recByRow(int row) const
{
  qlonglong id = idByRow(row);
  if (_changesHash.contains(id) && !_changesHash.value(id).isEmpty()) {
    return _changesHash.value(id);
  }
  else
    return _dataHash.value(id);
}

qlonglong UniSqlTableModel::idByRow(int row) const
{
  if (row < 0 || row >= rowCount())
    return -1;
  return _rowIndex.at(row);
}

QVariant UniSqlTableModel::primaryValue(int row) const
{
  if (_primaryKey.count() != 1)
    return QVariant();
  QSqlRecord rec = recByRow(row);
  return rec.value(_primaryKey.fieldName(0));
}

QString UniSqlTableModel::fields()
{
  QStringList fields;
  for(int idx=0; idx<_patternRec.count(); idx++) {
    fields << _patternRec.fieldName(idx);
  }
  return fields.join(", ");
}

QString UniSqlTableModel::selectAllSql()
{
  qDebug() << "Pattern rec:" << _patternRec;
  QString stmt;
  if (_patternRec.isEmpty()) {
    stmt = QString("SELECT * FROM %1").arg(tableName());
  }
  else {
    stmt = db().driver()->sqlStatement(QSqlDriver::SelectStatement, tableName(),
                                            _patternRec, false);
  }
  QString where = _filterManager->whereClause();

  QString sql = Sql::concat(stmt, where);
  if (!_orderBy.isEmpty())
    sql = Sql::concat(sql, _orderBy);
  return sql;
}

bool UniSqlTableModel::select()
{
  QSqlQuery query = execDML(selectAllSql());
  if (query.lastError().isValid()){
    return false;
  }

  beginResetModel();
  clearData();
  //Fills index and data map with query result data
  while (query.next()){
    //Pattern rec from first result record
    if (_patternRec.isEmpty()) {
      _patternRec = query.record();
    }

    qlonglong id = getId(query);
    _rowIndex.append(id);
    _dataHash.insert(id, query.record());
  }
  endResetModel();

  return true;
}

bool UniSqlTableModel::isDirty()
{
  return !_changesHash.isEmpty();
}

bool UniSqlTableModel::submitAll(bool stopOnError)
{
  QHashIterator<qlonglong, QSqlRecord> it(_changesHash);
  while(it.hasNext()) {
    if (!submitById(it.next().key()) && stopOnError)
      return false;
  }
  return true;
}

bool UniSqlTableModel::submitById(qlonglong id)
{
  //This row was not changed actually
  if (!_changesHash.contains(id))
    return true;
  QSqlQuery query;
  //Insert action
  if (id < 0) {
    query = insertRowInTable(_changesHash.value(id));
    if (!query.lastError().isValid()) {
      qlonglong newId = 0;
      if (supportsReturning()) {
        query.next();
        newId = getId(query);
        _dataHash.insert(newId, query.record());
      }
      else {
        newId = genId();
        _dataHash.insert(newId, _changesHash.value(id));
      }
      _dataHash.remove(id);
      _changesHash.remove(id);

      int row = _rowIndex.indexOf(id);
      _rowIndex.replace(row, newId);
      //If inserted row data changed by trigger
      emit dataChanged(index(row, 0), index(row, rowCount()-1));
      emit headerDataChanged(Qt::Vertical, row, row);
    }
  }
  //Delete action
  else if (_changesHash.value(id).isEmpty()) {
    bool resOk = deleteRowInTable(_dataHash.value(id));
    if (resOk) {
      int delRow = _rowIndex.indexOf(id);
      beginRemoveRows(QModelIndex(), delRow, delRow);
      _rowIndex.removeAt(delRow);
      _dataHash.remove(id);
      _changesHash.remove(id);
      endRemoveRows();
    }
  }
  //Update action
  else {
    query = updateRowInTable(_dataHash.value(id), _changesHash.value(id));
    if (!query.lastError().isValid()) {
      _dataHash.insert(id, _changesHash.value(id));
      _changesHash.remove(id);
    }
  }
  return !query.lastError().isValid();
}

bool UniSqlTableModel::selectRowInTable(QSqlRecord &values)
{
  QSqlRecord whereValues = values.keyValues(_primaryKey);
  QSqlDatabase conn = db();
  QString stmt = conn.driver()->sqlStatement(QSqlDriver::SelectStatement, tableName(),
                                                   values, false);
  QString where = conn.driver()->sqlStatement(QSqlDriver::WhereStatement, tableName(),
                                                     whereValues, false);
  QString sql = Sql::concat(stmt, where);
  QSqlQuery query = execDML(sql);
  //Query was successfully executed and returns a record
  if (!query.lastError().isValid() && query.next()){
    QSqlRecord resRec = query.record();
    for(int i = 0; i < resRec.count(); i++){
      values.setValue(i, resRec.value(i));
    }
    return true;
  }
  return false;
}

QSqlQuery UniSqlTableModel::updateRowInTable(const QSqlRecord &oldValues, const QSqlRecord &newValues)
{
  QSqlRecord whereValues = noPk() ? oldValues : oldValues.keyValues(_primaryKey);

  QSqlDatabase conn = db();
  QString stmt = conn.driver()->sqlStatement(QSqlDriver::UpdateStatement, tableName(),
                                            newValues, false);
  QString where = conn.driver()->sqlStatement(QSqlDriver::WhereStatement, tableName(),
                                             whereValues, false);
  QString sql = Sql::concat(stmt, where);
  return execDML(sql);
}

QSqlQuery UniSqlTableModel::insertRowInTable(const QSqlRecord &values)
{
  QSqlRecord vals(values);
  //Remove fields with NULL-values
  for(int idx=values.count()-1; idx >= 0; idx--) {
    if (!values.field(idx).defaultValue().isNull() && values.field(idx).value().isNull())
      vals.remove(idx);
  }
  QString stmt = db().driver()->sqlStatement(QSqlDriver::InsertStatement, tableName(),
                                                   vals, false);
  if (supportsReturning()) {
    stmt.append(Sql::sp()).append("RETURNING").append(Sql::sp()).append(fields());
  }
  return execDML(stmt);
}

bool UniSqlTableModel::deleteRowInTable(const QSqlRecord &values)
{
  QSqlRecord whereValues = noPk() ? values : values.keyValues(_primaryKey);
  QSqlDatabase conn = db();
  QString stmt = conn.driver()->sqlStatement(QSqlDriver::DeleteStatement, tableName(),
                                            values, false);
  QString where = conn.driver()->sqlStatement(QSqlDriver::WhereStatement, tableName(),
                                             whereValues, false);
  QString sql = Sql::concat(stmt, where);
  return execDDL(sql);
}

QSqlDatabase UniSqlTableModel::db()
{
  return QSqlDatabase::database(_connectionName);
}


bool UniSqlTableModel::revertAll()
{
  beginResetModel();
  QHashIterator<qlonglong, QSqlRecord> it(_changesHash);
  while(it.hasNext()) {
    it.next();
    //Added but not submitted rows
    if (it.key() < 0) {
      _rowIndex.removeOne(it.key());
    }
  }
  _changesHash.clear();
  endResetModel();
  return true;
}

SqlFilterManager *UniSqlTableModel::filter()
{
  return _filterManager;
}

void UniSqlTableModel::orderBy(QString field, Qt::SortOrder direction)
{
  QString orderByPattern = " ORDER BY %1 %2";
  _orderBy = orderByPattern.arg(field, direction == Qt::AscendingOrder ? "ASC" : "DESC");
}

QString UniSqlTableModel::tableName()
{
  return db().driver()->escapeIdentifier(_tableName, QSqlDriver::TableName);
}

QString UniSqlTableModel::fieldName(int idx)
{
  return _patternRec.fieldName(idx);
}

int UniSqlTableModel::fieldIndex(QString name)
{
  return _patternRec.indexOf(name);
}

QStringList UniSqlTableModel::sqlError()
{
  QStringList res = _sqlErrors;
  _sqlErrors.clear();
  return res;
}

int UniSqlTableModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return _rowIndex.count();
}

int UniSqlTableModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return _patternRec.count();
}

QVariant UniSqlTableModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();
  if (role == Qt::DisplayRole || role == Qt::EditRole) {
    QSqlRecord rec = recByRow(index.row());
    return rec.value(index.column());
  }

  return QVariant();
}

bool UniSqlTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (!index.isValid())
    return false;
  if (role == Qt::EditRole) {
    qlonglong id = _rowIndex.at(index.row());
    QSqlRecord rec = recByRow(index.row());
    if (rec.value(index.column()) == value) {
      qDebug() << "setData(): Value not changed";
      return false;
    }
    rec.setValue(index.column(), value);
    _changesHash.insert(id, rec);
    return true;
  }
  return false;
}

QVariant UniSqlTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (section < 0)
    return QVariant();

  if (orientation == Qt::Horizontal) {
    if (role == Qt::DisplayRole)
      return _patternRec.fieldName(section);
  }
  else {
    qlonglong id = idByRow(section);
    if (role == Qt::DisplayRole) {
      if (id < 0)
        return "+";
      else if (_changesHash.contains(id) && _changesHash.value(id).isEmpty()) {
        return "-";
      }
      else
        return section + 1;
    }
    else if (role == Qt::BackgroundRole) {
      if (id < 0)
        return QColor(Qt::green);
      else if (_changesHash.contains(id) && _changesHash.value(id).isEmpty()) {
        return QColor(Qt::red);
      }
    }
  }
  return QVariant();
}

Qt::ItemFlags UniSqlTableModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::NoItemFlags;
  return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}


bool UniSqlTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
  //Works only for table models and only one row at time
  if (parent.isValid() || count > 1)
    return false;

  QSqlRecord newRec(_patternRec);

  beginInsertRows(parent, row, row + count - 1);
  qlonglong fakeId = genTempId();
  _rowIndex.append(fakeId);
  _changesHash.insert(fakeId, newRec);
  endInsertRows();
  return true;
}

bool UniSqlTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
  //Works only for table models and only one row at a time
  if (parent.isValid() || count > 1)
    return false;

  qlonglong delId = idByRow(row);
  QSqlRecord dummyRec;
  _changesHash.insert(delId, dummyRec);
  emit headerDataChanged(Qt::Vertical, row, row);

  return true;
}
