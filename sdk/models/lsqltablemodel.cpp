#include "lsqltablemodel.h"
#include <QDebug>
#include <QSqlError>
#include "objects/appconst.h"
#include "utils/sqlutils.h"

/*!
    \class LSqlTableModel
    \brief The alternative to standard QSqlTable model class that provides an editable data model
    for a single database table.

    The main idea of LSqlTableModel is to avoid full table reselection after rows deletion
    and creation. There isn't any caching for \c removeRow() operation though row modification and
    new rows creation is cached until \c submit or \c revert methods called.
    
*/

LSqlTableModel::LSqlTableModel(QObject *parent, QSqlDatabase db) :
  QAbstractTableModel(parent)
{
  _db = db.isValid() ? db : QSqlDatabase::database();
  _query = QSqlQuery(_db);
  _autoIncrementID = db.driver()->hasFeature(QSqlDriver::LastInsertId);

  _filterManager = new SqlFilterManager(this);
}

/*!
    Sets the database table the model should be populated with
*/
bool LSqlTableModel::setTable(QString tableName)
{
  _tableName = tableName;
  QString preparedName = _db.driver()->escapeIdentifier(_tableName, QSqlDriver::TableName);
  _patternRec = _db.record(preparedName);
  _primaryIndex = _db.primaryIndex(preparedName);
  return true;
}

void LSqlTableModel::setSort(int colIndex, Qt::SortOrder sortOrder)
{
  setSort(_patternRec.field(colIndex).name(), sortOrder);
}

void LSqlTableModel::setSort(QString colName, Qt::SortOrder sortOrder)
{
  QString orderByPattern = "order by %1 %2";
  _orderByClause = orderByPattern.arg(colName,
                                      sortOrder == Qt::AscendingOrder ? "asc" : "desc");
}

QString LSqlTableModel::tableName()
{
  return _db.driver()->escapeIdentifier(_tableName, QSqlDriver::TableName);
}

SqlFilterManager *LSqlTableModel::filter()
{
  return _filterManager;
}

void LSqlTableModel::setHeaders(QStringList strList)
{
  _headers.clear();
  _headers.append(strList);
  emit headerDataChanged(Qt::Horizontal, 0, _headers.count() - 1);
}

void LSqlTableModel::addLookupField(LSqlTableModel *lookupModel, QString keyField, QString lookupField)
{
  LLookupField field = LLookupField();
  field.lookupModel = lookupModel;
  field.keyField = keyField;
  field.lookupField = lookupField;
  _lookupFields.append(field);
  //Changes in lookup model considered as changes of the model
  //TODO: this situation should be handled more correctly
  connect(lookupModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
          this, SIGNAL(dataChanged(QModelIndex,QModelIndex)));
}

int LSqlTableModel::fieldIndex(QString fieldName) const
{
  int index = _patternRec.indexOf(fieldName);
  if (index < 0){
    for(int i=0; i<_lookupFields.count(); i++){
      if (_lookupFields.at(i).lookupField == fieldName)
        return _patternRec.count() + i;
    }
  }
  if (index < 0)
    qDebug() << "Model" << objectName() << "contains no field named" << fieldName;
  return index;
}

QString LSqlTableModel::fieldName(int col) const
{
  if (col < 0 || col >= _patternRec.count())
    return "";
  return _patternRec.fieldName(col);
}

QMetaType::Type LSqlTableModel::fieldType(int col) const
{
  if (col < 0 || col >= _patternRec.count())
    return QMetaType::UnknownType;
  return QMetaType::Type(_patternRec.field(col).metaType().id());
}

bool LSqlTableModel::isDirty(const QModelIndex &index) const
{
  if (!index.isValid())
    return false;
  LSqlRecord rec = _recMap[_recIndex[index.row()]];
  return rec.cacheAction() != LSqlRecord::None;
}

bool LSqlTableModel::isDirty() const
{
  return _modified;
}

void LSqlTableModel::setCacheAction(qlonglong recId, LSqlRecord::CacheAction action)
{
  setCacheAction(_recMap[recId], action);
}

void LSqlTableModel::setSequenceName(QString name)
{
  _sequenceName = name;
  _autoIncrementID = _sequenceName.isEmpty();
}

/*!
    Populates the model with table data
*/
bool LSqlTableModel::select()
{
  if (!execQuery(selectAllSql())){
    return false;
  }
  beginResetModel();
  clearData();
  //Fills index and data map with query result data
  while (_query.next()){
    _recIndex.append(_query.value(F_ID).toLongLong());
    _recMap.insert(_query.value(F_ID).toLongLong(), LSqlRecord(_query.record()));
  }
  endResetModel();

  return true;
}

bool LSqlTableModel::submitRow(int row)
{
  qlonglong id = _recIndex.at(row);
  return submitRecord(_recMap[id]);
}

/*!
    Trys to submit all cached (unsaved) changes to the database table.
    Returns \c true if all cached changes were successfully submitted.
*/
bool LSqlTableModel::submitAll()
{
  //Nothing to submit
  if (!_modified)
    return true;

  CacheMap::Iterator it;
  bool result = true;
  for (it = _recMap.begin(); it != _recMap.end(); ++it){
    result &= submitRecord(it.value());
  }
  _modified = !result;
  return result;
}

/*!
    Returns number of rows that the model contains
*/
int LSqlTableModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return _recMap.count();
}

/*!
    Returns number of columns tha the model contains
*/
int LSqlTableModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return _patternRec.count() + _lookupFields.count();
}

/*!
    Overriden virtual method that returns the model data for roles \c Qt::DisplayRole and
    \c Qt::EditRole.
*/
QVariant LSqlTableModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();
  switch (role) {
  case Qt::DisplayRole:
  case Qt::EditRole:
  {
    LSqlRecord rec = _recMap[_recIndex.at(index.row())];
    if (index.column() >= rec.count()){
      LLookupField lookupField = _lookupFields.at(index.column() - rec.count());
      qlonglong key = rec.value(lookupField.keyField).toLongLong();
      return lookupField.data(key);
    }
    else {
      return rec.value(index.column());
    }
  }
  default:
    return QVariant();
  }
}

/*!
    Overloaded convinient method data() to get item value by row and column name.
*/
QVariant LSqlTableModel::data(int row, QString columnName, int role)
{
  QModelIndex index = this->index(row, fieldIndex(columnName));
  return data(index, role);
}

/*!
    Overriden virtual method that used to save the data to the model.
    Rows modified by this method would be marked with cache action \c LSqlRecord::Update
    unless they are already marked with cache action \c LSqlRecord::Insert.
*/
bool LSqlTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  //TODO: isNull(index) condition should be checked
  if (role == Qt::EditRole) {
    LSqlRecord &rec = _recMap[_recIndex.at(index.row())];

    QVariant oldVal = rec.value(index.column());
    QMetaType fieldType = _patternRec.field(index.column()).metaType();
    QVariant newVal = sqlValue(value, QMetaType::Type(fieldType.id()));
    if (oldVal != newVal || oldVal.isNull() != newVal.isNull()){
      qDebug() << "Record" << index.row() << "updated:"
               << oldVal << "->" << newVal;
      if (newVal.isNull())
        rec.setNull(index.column());
      else
        rec.setValue(index.column(), newVal);
      setCacheAction(rec, LSqlRecord::Update);
      emit dataChanged(index, index);
      return true;

    }
  }
  return false;
}

bool LSqlTableModel::setData(int row, QString columnName, QVariant value, int role)
{
  QModelIndex index = this->index(row, fieldIndex(columnName));
  return setData(index, value, role);
}

/*!
    Overriden virtual method that manages properties of model items
    (such as \c Qt::ItemIsEnabled Qt::ItemIsSelectable  Qt::ItemIsEditable)
*/
Qt::ItemFlags LSqlTableModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::NoItemFlags;
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

/*!
    Overriden virtual method that manages header item data of a view widget
*/
QVariant LSqlTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role == Qt::DisplayRole){
    if (orientation == Qt::Vertical){
      return section;
    }
    else {
      if (_headers.count() > section) {
        return _headers[section];
      }
      else {
        if (_patternRec.count() > section)
          return _patternRec.fieldName(section);
        else
          return _lookupFields.at(section -_patternRec.count()).lookupField;
      }
    }
  }
  return QVariant();
}

/*!
    Inserts new row into the model. Supports adding of only one row at a time.
    Primary key value of a new record filled through \c nextId() call. Other record
    fields can be filled with initial values by handling signal \c beforeInsert(QSqlRecord)
*/
bool LSqlTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
  //Works only for table models and only one row at time
  if (parent.isValid() || count > 1)
    return false;

  LSqlRecord newRec(_patternRec);
  newRec.clearValues();

  //Trying to get next id value
  qlonglong newId;
  //Autoincrement ID field
  if (_autoIncrementID || returningInsertMode()) {
    //Set temprary (negative) ID value
    newId = -(++_insertedCount);
  }
  else { //Sequence-based autoincrement
    newId = nextSequenceNumber();
    if (newId < 0)
      return false;
  }
  newRec.setValue(F_ID, QVariant(newId));

  //Signal to initialize the row with default values
  emit beforeInsert(newRec);

  setCacheAction(newRec, LSqlRecord::Insert);

  beginInsertRows(parent, row, row + count - 1);
  _recIndex.insert(row, newId);
  _recMap.insert(newId, newRec);
  endInsertRows();
  return true;
}

/*!
    Removes row from the model and deletes the corresponding record from
    the database table. The operation isn't cachable unlike QSqlTableModel.
*/
bool LSqlTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
  //Works only for table models and only one row at a time
  if (parent.isValid() || count > 1)
    return false;

  //No need to delete record in DB if it isn't there yet
  if (_recMap.value(_recIndex[row]).cacheAction() != LSqlRecord::Insert){
    QSqlRecord delRec(_primaryIndex);
    delRec.setValue(F_ID, static_cast<qlonglong>(_recIndex.at(row)));

    if (!deleteRowInTable(delRec))
      return false;
  }

  beginRemoveRows(parent, row, row + count - 1);
  _recMap.remove(_recIndex[row]);
  _recIndex.removeAt(row);
  endRemoveRows();
  return true;
}

QSqlRecord LSqlTableModel::record(int row) const
{
  return _recMap.value(_recIndex[row]);
}

int LSqlTableModel::rowByValue(QString field, QVariant value)
{
  int fieldIdx = fieldIndex(field);
  if (fieldIdx < 0)
    return -1;
  for (int i=0; i<rowCount(); i++){
    QSqlRecord rec = record(i);
    if (rec.value(fieldIdx) == value)
      return i;
  }
  return -1;
}

QSqlRecord* LSqlTableModel::recordById(qlonglong id)
{  
  return _recMap.contains(id) ? &_recMap[id] : nullptr;
}

/*!
    Sets cache operation mark for the model row.
*/
void LSqlTableModel::setCacheAction(LSqlRecord &rec, LSqlRecord::CacheAction action)
{
  //Row that was inserted keeps LSqlRecord::Insert status after editing
  if (rec.cacheAction() == LSqlRecord::Insert && action == LSqlRecord::Update)
    return;

  rec.setCacheAction(action);
  if (action != LSqlRecord::None && !_modified)
    _modified = true;
}

/*!
    Submit cached changes to the corresponding database table record
*/
bool LSqlTableModel::submitRecord(LSqlRecord &rec)
{
  //Record is not modified
  if (rec.cacheAction() == LSqlRecord::None)
    return true;

  bool result = true;
  if (rec.cacheAction() == LSqlRecord::Update){
    result = updateRowInTable(rec);
  }
  else if (rec.cacheAction() == LSqlRecord::Insert) {
    //Clear temporary ID for DB autoincrement
    if (rec.value(F_ID).toLongLong() < 0)
      rec.setValue(F_ID, QVariant());
    result = insertRowInTable(rec);
    //Update ID with generated value
    if (result && _autoIncrementID)
      rec.setValue(F_ID, _query.lastInsertId());
    if (result && returningInsertMode() && _query.next())
      rec.setValue(F_ID, _query.value(0));
  }
  if (result){
    setCacheAction(rec, LSqlRecord::None);
  }
  else {
    qDebug() << "Error while submitting record: " << rec;
  }
  return result;
}

/*!
  Revert all cached changes to the model data.
  Note: Remove operation connot be cached unlike QSqlTableModel.
*/
bool LSqlTableModel::revertAll()
{
  //No changes to the model
  if (!_modified)
    return true;

  bool result = true;
  int row = 0;
  while (row < _recIndex.count()){
    switch(_recMap[_recIndex[row]].cacheAction()){
    case LSqlRecord::Insert:
      beginRemoveRows(QModelIndex(), row, row);
      _recMap.remove(_recIndex[row]);
      _recIndex.removeAt(row);
      endRemoveRows();
      break;
    case LSqlRecord::Update:
      result &= reloadRow(row);
      row++;
      break;
    default:
      row++;
    }
  }
  _modified = !result;

  return result;
}

bool LSqlTableModel::reloadRow(int row)
{
  LSqlRecord& rec = _recMap[_recIndex[row]];
  if (rec.cacheAction() != LSqlRecord::Update)
    return true;
  bool result = selectRowInTable(rec);
  if (result){
    rec.setCacheAction(LSqlRecord::None);
    //Signal for views that row was updated
    emit dataChanged(createIndex(row, 0), createIndex(row, columnCount() - 1));
  }
  return result;
}

/*!
  Check if field corresponding to index marked by isNull flag
*/
bool LSqlTableModel::isNull(const QModelIndex &index)
{
  if (!index.isValid())
    return true;
  LSqlRecord& rec = _recMap[_recIndex[index.row()]];
  QSqlField field = rec.field(index.column());
  return field.isNull();
}

QVariant LSqlTableModel::sqlValue(QVariant val, QMetaType::Type type)
{
  QVariant varVal;
  varVal.convert(QMetaType(type));

  if (!val.isValid())
    return varVal;

  if (val.toString().isEmpty()) {
    if (type == QMetaType::QString)
      return "";
    else
      return varVal;
  }
  else {
    return val;
  }
}

bool LSqlTableModel::selectRowInTable(QSqlRecord &values)
{
  QSqlRecord whereValues = primaryValues(values);
  QString stmt = _db.driver()->sqlStatement(QSqlDriver::SelectStatement, _tableName,
                                            values, false);
  QString where = _db.driver()->sqlStatement(QSqlDriver::WhereStatement, _tableName,
                                             whereValues, false);
  QString sql = Sql::concat(stmt, where);
  bool result = execQuery(sql);
  //Query was successfully executed and returns a record
  if (result && _query.next()){
    QSqlRecord resRec = _query.record();
    for(int i = 0; i < resRec.count(); i++){
      values.setValue(i, resRec.value(i));
    }
    return true;
  }
  return false;
}

bool LSqlTableModel::updateRowInTable(const QSqlRecord &values)
{
  QSqlRecord rec(values);
  QSqlRecord whereValues = primaryValues(values);

  QString stmt = _db.driver()->sqlStatement(QSqlDriver::UpdateStatement, tableName(),
                                            rec, false);
  QString where = _db.driver()->sqlStatement(QSqlDriver::WhereStatement, tableName(),
                                             whereValues, false);
  QString sql = Sql::concat(stmt, where);
  return execQuery(sql);
}

bool LSqlTableModel::insertRowInTable(const QSqlRecord &values)
{
  QString stmt = _db.driver()->sqlStatement(QSqlDriver::InsertStatement, tableName(),
                                            values, false);
  if (returningInsertMode())
    stmt.append(Sql::sp() + "RETURNING ID");
  return execQuery(stmt);
}

bool LSqlTableModel::deleteRowInTable(const QSqlRecord &values)
{
  QSqlRecord rec(values);
  QString stmt = _db.driver()->sqlStatement(QSqlDriver::DeleteStatement, tableName(),
                                            rec, false);
  QString where = _db.driver()->sqlStatement(QSqlDriver::WhereStatement, tableName(),
                                             values, false);
  QString sql = Sql::concat(stmt, where);
  return execQuery(sql);
}

void LSqlTableModel::clearData()
{
  _recIndex.clear();
  _recMap.clear();
}

QSqlRecord LSqlTableModel::primaryValues(QSqlRecord rec) const
{
  QSqlRecord r(_primaryIndex);
  for (int i=0; i<r.count(); i++){
    r.setValue(i, rec.value(r.fieldName(i)));
  }
  return r;
}

qlonglong LSqlTableModel::primaryKey(int row, int part)
{
  if (part >= _primaryIndex.count())
    part = 0;
  return data(row, primaryKeyName(part)).toLongLong();
}

QString LSqlTableModel::primaryKeyName(int part)
{
  Q_ASSERT(part >= 0);
  return _primaryIndex.fieldName(part);
}

int LSqlTableModel::primaryKeyCount()
{
  return _primaryIndex.count();
}

QString LSqlTableModel::selectAllSql()
{
  QString stmt = _db.driver()->sqlStatement(QSqlDriver::SelectStatement, tableName(),
                                            _patternRec, false);
  QString where = _filterManager->whereClause();
  return Sql::concat(Sql::concat(stmt, where), _orderByClause);
}

/*!
    Returns a subsequent value of the database generator (sequence).
    Name of the generator can be set by method \c setSequenceName.
*/
qlonglong LSqlTableModel::nextSequenceNumber()
{
  if (_sequenceName.isEmpty()){
    qDebug() << "No sequence specified for table " << _tableName;
    return -1;
  }

  QString sql = "select GEN_ID(%1, 1) from rdb$database";
  if (!execQuery(sql.arg(_sequenceName))){
    qDebug() << "Error handling sequence: " << _sequenceName;
    return -1;
  }
  _query.next();
  return _query.value(0).toLongLong();
}

bool LSqlTableModel::returningInsertMode()
{
  return _db.driverName() == DRIVER_FIREBIRD && _sequenceName.isEmpty();
}

/*!
    A wrapper function for all sql-queries.
    Sends all executed sql-queries to qDebug() in case
    of success and error messages in case of failure.
*/
bool LSqlTableModel::execQuery(const QString &sql)
{
  bool result = _query.exec(sql);
#ifdef DEBUG_SQL
  qDebug() << "Execute query: " << sql;
  if (!result){
    QString desc = "Error: " + _query.lastError().databaseText();
    qDebug() << desc;
    emit error(desc);
  }
#endif
  return result;
}

QVariant LSqlTableModel::execQuery(const QString &sql, QString resColumn)
{
  if (execQuery(sql) && _query.next()){
    return _query.value(resColumn);
  }
  else {
    return QVariant();
  }
}


LSqlRecord::LSqlRecord(): QSqlRecord()
{
  _cacheAction = LSqlRecord::None;
}

LSqlRecord::LSqlRecord(const QSqlRecord &rec): QSqlRecord(rec)
{
  _cacheAction = LSqlRecord::None;
}

QVariant LLookupField::data(qlonglong key)
{
  QSqlRecord* rec = lookupModel->recordById(key);
  if (rec == nullptr){
    return QVariant();
  }
  else {
    return rec->value(lookupField);
  }
}
