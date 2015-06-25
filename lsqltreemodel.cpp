#include "lsqltreemodel.h"
#include <QDebug>


LSqlTreeModel::LSqlTreeModel(QObject *parent, QSqlDatabase db) :
    QAbstractItemModel(parent)
{
  _db = db.isValid() ? db : QSqlDatabase::database();
  _query = QSqlQuery(_db);
}

LSqlTreeModel::~LSqlTreeModel()
{
}

qlonglong LSqlTreeModel::itemParentId(LSqlTreeRecord rec) const
{
  return rec.value(_parentField).toLongLong();
}

QModelIndex LSqlTreeModel::indexById(qlonglong id)
{
  if (!_recMap.contains(id))
    return QModelIndex();
  LSqlTreeRecord itemRec = _recMap[id];
  qlonglong parentId = itemParentId(itemRec);
  int row;
  if (parentId == 0){
    row = _rootRecList.indexOf(id);
  }
  else {
    LSqlTreeRecord parentRec = _recMap[parentId];
    row = parentRec.childIndex(id);
  }
  return createIndex(row, 0, id);
}

void LSqlTreeModel::clear()
{
  _recMap.clear();
  _rootRecList.clear();
}

void LSqlTreeModel::addRecord(LSqlTreeRecord rec)
{
  qlonglong parentId = itemParentId(rec);

  if (parentId == 0){
    _rootRecList.append(rec.id());
  } else if (!_recMap.contains(parentId)){
    //Указанный родитель не найден
    return;
  } else {
    _recMap[parentId].addChild(rec.id());
  }
  QModelIndex parentIdx = indexById(parentId);
  int childCount = rowCount(parentIdx);
  beginInsertRows(parentIdx, childCount - 1, rowCount(parentIdx) - 1);
  _recMap.insert(rec.id(), rec);
  endInsertRows();
}

bool LSqlTreeModel::setTable(QString tableName)
{
  _tableName = tableName;
  _patternRec = _db.record(_tableName);
  _primaryIndex = _db.primaryIndex(_tableName);
  return true;
}

bool LSqlTreeModel::select()
{
  QString selectAllSql = "select * from %1";
  if (!execQuery(selectAllSql.arg(_tableName))){
    return false;
  }
  beginResetModel();
  clear();

  while (_query.next()){
    qlonglong parentId = _query.value(_parentField).toLongLong();
    qlonglong id = _query.value(PRIMARY_KEY_FIELD).toLongLong();
    if (_recMap.contains(id)){
      _recMap[id].copyValues(_query.record());
    }
    else {
      _recMap.insert(id, LSqlTreeRecord(_query.record()));
    }
    if (parentId == 0){
      _rootRecList.append(id);
    }
    else {
      if (!_recMap.contains(parentId)){
        _recMap.insert(parentId, LSqlTreeRecord(_patternRec));
      }
      _recMap[parentId].addChild(id);
    }
  }
  endResetModel();

  return true;
}

QModelIndex LSqlTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();    

    qlonglong childId;

    //Если родительский индекс невалидный, значит это корневой элемент
    if (!parent.isValid()){
      childId = _rootRecList.at(row);
    }
    //получаем элемент родителя и по номеру элемента получает ID
    else {
      LSqlTreeRecord parentRec = _recMap[parent.internalId()];
      childId = parentRec.childByIndex(row);
    }        
    if (childId > 0)
      return createIndex(row, column, childId);
    else
      return QModelIndex();
}

QModelIndex LSqlTreeModel::parent(const QModelIndex &child) const
{
  if (!child.isValid())
    return QModelIndex();

  //получаем ID родительского элемента
  LSqlTreeRecord childItem = _recMap[child.internalId()];
  qlonglong parentId = itemParentId(childItem);
  //если PARENT_ID не заполнен, значит родительского элемента нет
  if (parentId == 0){
    return QModelIndex();
  }
  else {
    //получаем ID дедушки
    LSqlTreeRecord parentRec = _recMap[parentId];
    qlonglong grandParentId = itemParentId(parentRec);
    int parentRowIndex;
    //если не удалось получить ID дедушки, значит родитель - корневой элемент
    if (grandParentId == 0){
      parentRowIndex = _rootRecList.indexOf(parentId);
    }
    else {      
      //находим номер родителя в списке дедушкиных детей
      LSqlTreeRecord grandParentItem = _recMap[grandParentId];
      parentRowIndex = grandParentItem.childIndex(parentId);
    }
    return createIndex(parentRowIndex, 0, parentId);
  }
}

int LSqlTreeModel::rowCount(const QModelIndex &parent) const
{
  //дочерние элементы есть только у первой колонки
  if (parent.column() > 0)
    return 0;

  //если родительский индекс невалидный, возвращаем кол-во корневых элементов
  if (!parent.isValid()){
    return _rootRecList.count();
  }
  else {
    //возвращаем кол-во дочерних элементов
    LSqlTreeRecord parentRec = _recMap[parent.internalId()];
    return parentRec.childCount();
  }
}

int LSqlTreeModel::columnCount(const QModelIndex &parent) const
{
  //кол-во колонок таблицы
  return _patternRec.count();
}

QVariant LSqlTreeModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  //получаем запись таблицы по ID
  LSqlTreeRecord rec = _recMap[index.internalId()];
  int column = index.column();

  switch (role) {
  case Qt::DisplayRole:    
    return rec.value(column);
    break;
  default:
    return QVariant();
    break;
  }
}

void LSqlTreeModel::setParentField(QString name)
{
  _parentField = name;
}

LSqlTreeRecord LSqlTreeModel::patternRec() const
{
  return _patternRec;
}

int LSqlTreeModel::fieldIndex(QString fieldName) const
{
  return _patternRec.indexOf(fieldName);
}

LSqlTreeRecord LSqlTreeModel::recById(qlonglong id) const
{
  return _recMap[id];
}

bool LSqlTreeModel::execQuery(const QString &sql)
{
  bool result = _query.exec(sql);
  qDebug() << "Execute query: " << sql;
  if (!result){
    qDebug() << "Error: " << _query.lastError().databaseText();
  }
  return result;
}

QVariant LSqlTreeModel::execQuery(const QString &sql, QString resColumn)
{
  if (execQuery(sql) && _query.next()){
    return _query.value(resColumn);
  }
  else {
    return QVariant();
  }
}

LSqlTreeRecord::LSqlTreeRecord(): QSqlRecord()
{
}

LSqlTreeRecord::LSqlTreeRecord(const QSqlRecord &rec): QSqlRecord(rec)
{
}

LSqlTreeRecord::~LSqlTreeRecord()
{
}

void LSqlTreeRecord::copyValues(const QSqlRecord &rec)
{
  for (int i=0; i<rec.count(); i++){
    setValue(i, rec.value(i));
  }
}

void LSqlTreeRecord::addChild(long childId)
{
  _childIdList.append(childId);
}

void LSqlTreeRecord::removeChild(long childId)
{
  _childIdList.removeOne(childId);
}

int LSqlTreeRecord::childIndex(qlonglong childId)
{
  return _childIdList.indexOf(childId);
}

qlonglong LSqlTreeRecord::childByIndex(int index)
{
  return _childIdList.value(index);
}

int LSqlTreeRecord::childCount()
{
  return _childIdList.count();
}


QVariant LSqlTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  switch (role) {
  case Qt::DisplayRole:
    return _patternRec.fieldName(section);
  default:
    return QVariant();
  }
}


bool LSqlTreeModel::removeRows(int row, int count, const QModelIndex &parent)
{
  LSqlTreeRecord& parentRec = _recMap[parent.internalId()];
  beginRemoveRows(parent, row, row + count);
  for(int i=0; i<count; i++){
    qlonglong childId = parentRec.childByIndex(row);
    parentRec.removeChild(childId);
    removeChildren(childId);
    _recMap.remove(childId);
  }
  endRemoveRows();
  return true;
}

bool LSqlTreeModel::removeChildren(qlonglong parentId)
{
  LSqlTreeRecord parentRec = recById(parentId);
  while(parentRec.childCount() > 0){
    qlonglong childId = parentRec.childByIndex(0);
    parentRec.removeChild(childId);
    removeChildren(childId);
    _recMap.remove(childId);
  }
  return true;
}

bool LSqlTreeModel::removeAllChildren(const QModelIndex &parent)
{
  int childCount = recById(parent.internalId()).childCount();
  removeRows(0, childCount, parent);
}

bool LSqlTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

}
