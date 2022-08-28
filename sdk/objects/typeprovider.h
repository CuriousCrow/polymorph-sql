#ifndef TYPEPROVIDER_H
#define TYPEPROVIDER_H

#include <QObject>
#include <QAbstractTableModel>
#include "objects/dbobjectitem.h"


class DBType
{
public:
  virtual QString name() const = 0;
  virtual QString title() const = 0;
  virtual QVariant defValue() const = 0;
  virtual bool hasLength() const = 0;
  virtual bool hasScale() const = 0;
  virtual bool hasPrecision() const = 0;
  virtual bool isUserType() const = 0;
  virtual QString valueToSql(const QVariant &value) = 0;
};

class TypeProvider : public QAbstractTableModel
{
  Q_OBJECT
public:
  TypeProvider();
  QStringList typeNames() const;

  virtual DBType* type(QString name) const = 0;
  virtual QList<DBType*> types() const = 0;
};

class BaseDBType : public DBType
{
public:
  BaseDBType(QString name, QString caption = "");
protected:
  QString _name;
  QString _caption;

  // DBType interface
public:
  virtual QString name() const override;
  virtual QString title() const override;
  virtual QVariant defValue() const override;
  virtual bool hasLength() const override;
  virtual bool hasScale() const override;
  virtual bool hasPrecision() const override;
  virtual bool isUserType() const override;
};

class StringDBType : public BaseDBType
{
public:
  StringDBType(QString name, QString title = "");
  // DBType interface
public:
  virtual QString valueToSql(const QVariant &value) override;
};

class IntegerDBType : public BaseDBType
{
public:
  IntegerDBType(QString name, QString title = "");

  // DBType interface
public:
  virtual QString valueToSql(const QVariant &value) override;
};

class FloatDBType : public BaseDBType
{
public:
  FloatDBType(QString name, QString title = "");

  // DBType interface
public:
  virtual QString valueToSql(const QVariant &value) override;
};

class BlobDBType : public BaseDBType
{
public:
  BlobDBType(QString name, QString title = "");

  // DBType interface
public:
  virtual QString valueToSql(const QVariant &value) override;
};

class BaseTypeProvider : public TypeProvider
{
  Q_OBJECT
public:
  Q_INVOKABLE BaseTypeProvider();
  void setItemObject(DBObjectItem* itemObj);
protected:
  DBObjectItem* _itemObj;
  QList<DBType*> _types;

  // QAbstractItemModel interface
public:
  virtual int rowCount(const QModelIndex &parent) const override;
  virtual int columnCount(const QModelIndex &parent) const override;
  virtual QVariant data(const QModelIndex &index, int role) const override;

  // TypeProvider interface
public:
  virtual DBType *type(QString name) const override;
  virtual QList<DBType *> types() const override;
};

#endif // TYPEPROVIDER_H
