#include "typeprovider.h"

TypeProvider::TypeProvider() : QAbstractTableModel()
{

}

QStringList TypeProvider::typeNames() const
{
  QStringList resList;
  foreach(DBType* type, types()) {
    resList.append(type->name());
  }
  return resList;
}



StringDBType::StringDBType(QString name, QString title) : BaseDBType(name, title)
{
}


QString StringDBType::valueToSql(const QVariant &value)
{
  return "'" + value.toString() + "'";
}


BaseDBType::BaseDBType(QString name, QString caption)
{
  this->_name = name;
  this->_caption = caption.isEmpty() ? _name : caption;
}


QString BaseDBType::name() const
{
  return _name;
}

QString BaseDBType::title() const
{
  return _caption;
}

QVariant BaseDBType::defValue() const
{
  return QVariant();
}

bool BaseDBType::hasLength() const
{
  return false;
}

bool BaseDBType::hasScale() const
{
  return false;
}

bool BaseDBType::hasPrecision() const
{
  return false;
}

bool BaseDBType::isUserType() const
{
  return false;
}

IntegerDBType::IntegerDBType(QString name, QString title) : BaseDBType(name, title)
{
}

QString IntegerDBType::valueToSql(const QVariant &value)
{
  return value.toString();
}

BaseTypeProvider::BaseTypeProvider() : TypeProvider()
{
}

void BaseTypeProvider::setItemObject(DBObjectItem *itemObj)
{
  this->_itemObj = itemObj;
}


int BaseTypeProvider::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return _types.count();
}

int BaseTypeProvider::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return 1;
}

QVariant BaseTypeProvider::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();
  if (role == Qt::DisplayRole) {
    DBType* type = _types.at(index.row());
    return type->name();
  }
  return QVariant();
}

DBType *BaseTypeProvider::type(QString name) const
{
  foreach(DBType* type, _types) {
    if (type->name() == name)
      return type;
  }
  return Q_NULLPTR;
}

QList<DBType *> BaseTypeProvider::types() const
{
  return _types;
}

FloatDBType::FloatDBType(QString name, QString title) : BaseDBType(name, title)
{
}

QString FloatDBType::valueToSql(const QVariant &value)
{
  return value.toString();
}

BlobDBType::BlobDBType(QString name, QString title) : BaseDBType(name, title)
{
}

QString BlobDBType::valueToSql(const QVariant &value)
{
  return value.toString();
}
