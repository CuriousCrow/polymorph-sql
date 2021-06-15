#include "ldbobjectmodel.h"
#include <QDebug>
#include "../objects/appconst.h"

//Поиск имени таблицы по алиасу
//(FROM|JOIN)\s+([^\s]+)\s+t


LDBObjectModel::LDBObjectModel(QObject *parent) : QAbstractTableModel(parent)
{
}

void LDBObjectModel::reload(QStringList keywords, QStringList functions, QString connName)
{
  qDebug() << connName;
  emit beginResetModel();
  _dataList.clear();
  foreach (QString keyword, keywords) {
    _dataList.append(DbObj(keyword, F_KEYWORD));
  }
  foreach (QString function, functions) {
    _dataList.append(DbObj(function, F_FUNCTION));
  }
  emit endResetModel();
}

DbObj LDBObjectModel::findByName(QString objName)
{
  foreach(DbObj obj, _dataList) {
    if (obj.name == objName)
      return obj;
  }
  return DbObj();
}

int LDBObjectModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)

  return _dataList.count();
}

int LDBObjectModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)

  return 2;
}

QVariant LDBObjectModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();
  if (role == Qt::DisplayRole || role == Qt::EditRole) {
    if (index.column() == 0)
      return _dataList.at(index.row()).name;
    else
      return _dataList.at(index.row()).type;
  }
  return QVariant();
}

DbObj::DbObj(QString name, QString type)
{
  this->name = name;
  this->type = type;
}
