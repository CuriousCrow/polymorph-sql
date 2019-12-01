#ifndef QDBOBJECTITEM_H
#define QDBOBJECTITEM_H

#include "lstandardtreemodel.h"
#include <QSqlDatabase>
#include <QUrl>

#define RES_OK_CODE 0
#define RES_BASE_ERROR 100
#define ERR_NOT_IMPLEMENTED 101
#define ERR_QUERY_ERROR 102

class ActionResult
{
public:
  ActionResult(int code = RES_OK_CODE, QString description = "");
  bool isSuccess();
  int resCode();
  QString description();
private:
  int _resultCode;
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

  bool isModified();
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
    Sequence,
    Trigger,
    Procedure,
    Folder,
    Field,
    Constraint,
    PrimaryKey,
    ForeignKey,
    UniqueConstraint,
    CheckConstraint
  };

  DBObjectItem(QString caption, QObject* parent = nullptr);
  ~DBObjectItem();
  QString connectionName(){ return _connectionName; }
  void setParentUrl(const QUrl &url);
  QString driverName();
  void deleteChildren();

  virtual bool reloadChildren() = 0;
  virtual QUrl objectUrl();
  virtual int type() = 0;
  virtual bool setData(int column, QVariant value, int role);
  virtual bool refresh();

  virtual ActionResult insertMe();
  virtual ActionResult updateMe();
  virtual ActionResult deleteMe();

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
  QUrl _parentUrl;
  QString _driverName;
  QList<DBObjectField> fields;
  int fieldIndex(QString fieldName);
  QString databaseName();
  DBObjectField field(QString fieldName);
  QString fillSqlPattern(QString pattern);
  QString fillSqlPattern(QString pattern, QMap<QString, QString> valueMap);
  QString fillPatternWithFields(QString pattern);
  QString fillWithModifiedFields(QString pattern);
  QString filterUnmodifiedFields(QString pattern);
  ActionResult execSql(QString sql, QString connectionName = "");

  // LAbstractTreeItem interface
public:
  virtual int colCount();
  virtual QVariant colData(int column, int role);
};

#endif // QDBOBJECTITEM_H
