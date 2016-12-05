#ifndef QDBOBJECTITEM_H
#define QDBOBJECTITEM_H

#include "lstandardtreemodel.h"
#include <QSqlDatabase>

class QDBObjectField
{
public:
  QDBObjectField(QString fieldName);
  QString name;

  QVariant value() const;
  void setValue(const QVariant &value);

  bool isModified();
  void submit();
  void revert();
private:
  QVariant _value;
  QVariant _oldValue;
};

class QDBObjectItem : public LAbstractTreeItem
{
  Q_OBJECT
public:
  enum ItemType {
    Database,
    Table,
    View,
    Sequence,
    Trigger,
    Procedure,
    Folder
  };

  QDBObjectItem(QString caption, QObject* parent = 0);
  ~QDBObjectItem();
  QString connectionName(){ return _connectionName; }

  virtual bool loadChildren() = 0;
  virtual QUrl objectUrl();
  virtual int type() = 0;
  virtual bool setData(int column, QVariant value, int role);

  virtual bool insertMe();
  virtual bool updateMe();
  virtual bool deleteMe();

  void registerField(QString fieldName);
  QVariant fieldValue(QString fieldName);
  QVariant fieldValue(int colNumber);
  void setFieldValue(QString fieldName, QVariant value);
  void setFieldValue(int colNumber, QVariant value);

  QStringList propertyList();
protected:
  QString _connectionName;  
  QList<QDBObjectField> fields;
  int fieldIndex(QString fieldName);
public slots:
  void updateObjectName();

  // LAbstractTreeItem interface
public:
  virtual int colCount();
  virtual QVariant colData(int column, int role);
};

#endif // QDBOBJECTITEM_H
