#ifndef DBOBJECTITEM_H
#define DBOBJECTITEM_H

#include "../models/lstandardtreemodel.h"
#include "abstractidentifiersupport.h"
#include <QSqlDatabase>
#include "appurl.h"

#define RES_OK_CODE 0
#define RES_BASE_ERROR 100
#define ERR_NOT_IMPLEMENTED 101
#define ERR_QUERY_ERROR 102
#define ERR_VALIDATION_ERROR 103

class ActionResult
{
public:
  ActionResult(int code = RES_OK_CODE, QString description = "");
  bool isSuccess() const;
  int resCode() const;
  QString description() const;
private:
  int _resultCode;
  QString _description;
};

class ObjectStatus
{
public:
  ObjectStatus(QString code, QString description);
  QString code();
  QString description();
private:
  QString _code;
  QString _description;
};

class DBObjectField
{
public:
  DBObjectField(QString fieldName);
  QString name;

  QVariant value() const;
  void setValue(const QVariant &value);

  QVariant oldValue() const;

  bool isModified() const;
  void submit();
  void revert();
private:
  QVariant _value;
  QVariant _oldValue;
};

class DBObjectItem : public LAbstractTreeItem
{
  Q_OBJECT
public:
  enum ItemType {
    UnknownType,
    Database,
    Table,
    View,
    SystemTable,
    Sequence,
    Trigger,
    Procedure,
    Folder,
    Field,
    Constraint,
    PrimaryKey,
    ForeignKey,
    UniqueConstraint,
    CheckConstraint,
    UserType
  };

  DBObjectItem(QString caption, QObject* parent = nullptr);
  virtual ~DBObjectItem();
  QString connectionName() const;

  void updateUrl();
  void setParentUrl(const AppUrl &url);
  QString driverName() const;
  void deleteChildren();
  QString caption() const;


  DBObjectItem* childItem(DBObjectItem::ItemType type, QString name = "");

  virtual bool reloadChildren() = 0;
  virtual AppUrl objectUrl();
  virtual int type() const = 0;
  virtual bool setData(int column, QVariant value, int role);
  virtual bool refresh();
  virtual ObjectStatus status() const;
  bool inStatus(QString status) const;
  //SQL export
  virtual QString toDDL() const;
  virtual QString toDML() const;

  virtual QStringList validate();
  virtual ActionResult insertMe();
  virtual ActionResult updateMe();
  virtual ActionResult deleteMe();

  bool isEditable() const;
  virtual bool isModified() const;
  virtual bool submit();
  virtual bool revert();

  bool hasField(QString fieldName) const;
  bool isEmptyField(QString fieldName) const;
  void registerField(QString fieldName);
  QVariant fieldValue(QString fieldName) const;
  QVariant fieldValue(int colNumber) const;
  QVariant fieldOldValue(QString fieldName) const;
  QVariant fieldOldValue(int colIdx) const;
  bool fieldModified(QString fieldName) const;
  void setFieldValue(QString fieldName, QVariant value);
  void copyFieldTo(QString fieldName, DBObjectItem* targetObj);
  void copyFieldsTo(DBObjectItem* targetObj);

  //Registering injected objects to be deleted in destructor
  void registerDependantObject(QObject* obj);

  static QString baseClassByType(ItemType type);
private:
  QList<QObject*> _dependantObjects;
  void setFieldValue(int colNumber, QVariant value);
  QString varToStr(QVariant variant) const;

protected:
  QString _connectionName;
  bool _editable = true;
  AppUrl _parentUrl;
  QString _driverName;
  AbstractIdentifierSupport* _identifierSupport;
  QList<DBObjectField> fields;
  int fieldIndex(QString fieldName) const;
  QString databaseName() const;
  DBObjectField& field(QString fieldName);
  QString identifier() const;
  virtual QString fillSqlPatternWithFields(QString pattern) const;
  QString fillSqlPatternWithFields(QString pattern, QMap<QString, QString> valueMap) const;
  QString fillWithModifiedFields(QString pattern) const;
  QString filterUnmodifiedFields(QString pattern) const;
  ActionResult execSql(QString sql, QString connectionName = QSqlDatabase::defaultConnection);
  void deleteInjected();

  // LAbstractTreeItem interface
public:
  virtual int colCount() const;
  virtual QVariant colData(int column, int role) const;
};

#endif // DBOBJECTITEM_H
