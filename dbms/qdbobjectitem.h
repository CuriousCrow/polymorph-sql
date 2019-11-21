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

  QVariant oldValue() const;

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
    UnknownType,
    Database,
    Table,
    View,
    Sequence,
    Trigger,
    Procedure,
    Folder,
    Field
  };

  QDBObjectItem(QString caption, QObject* parent = nullptr);
  ~QDBObjectItem();
  QString connectionName(){ return _connectionName; }
  void setDriverName(QString driverName);
  QString driverName();

  virtual bool loadChildren() = 0;
  virtual QUrl objectUrl();
  virtual int type() = 0;
  virtual bool setData(int column, QVariant value, int role);
  virtual bool refresh();

  virtual bool insertMe();
  virtual bool updateMe();
  virtual bool deleteMe();

  bool isEditable();
  virtual bool isModified();
  virtual bool submit();

  bool hasField(QString fieldName);
  void registerField(QString fieldName);
  QVariant fieldValue(QString fieldName);
  QVariant fieldValue(int colNumber);
  QVariant fieldOldValue(QString fieldName);
  QVariant fieldOldValue(int colIdx);
  bool fieldModified(QString fieldName);
  void setFieldValue(QString fieldName, QVariant value);
  void setFieldValue(int colNumber, QVariant value);

  QStringList propertyList();
protected:
  QString _connectionName;
  bool _editable = true;
  QList<QDBObjectField> fields;
  int fieldIndex(QString fieldName);
  QString databaseName();
  QDBObjectField field(QString fieldName);
  QString fillSqlPattern(QString pattern);
  QString fillSqlPattern(QString pattern, QMap<QString, QString> valueMap);
  QString fillPatternWithFields(QString pattern);
  QString fillWithModifiedFields(QString pattern);
  QString filterUnmodifiedFields(QString pattern);
public slots:
  void updateObjectName();

  // LAbstractTreeItem interface
public:
  virtual int colCount();
  virtual QVariant colData(int column, int role);
private:
  QString _driverName;
};

#endif // QDBOBJECTITEM_H
