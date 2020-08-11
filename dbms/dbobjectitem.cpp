#include "dbobjectitem.h"
#include <QDebug>

#include <QMetaProperty>
#include "qsqlqueryhelper.h"
#include "dbms/appconst.h"


DBObjectItem::DBObjectItem(QString caption, QObject* parent):
  LAbstractTreeItem(caption, parent)
{
  registerField(F_CAPTION);
  setFieldValue(F_CAPTION, caption);
}

DBObjectItem::~DBObjectItem()
{
}

void DBObjectItem::setParentUrl(const AppUrl &url)
{
  _parentUrl = url;
  AppUrl newUrl = objectUrl();
  _connectionName = newUrl.connection();
  _driverName = newUrl.driver();
  setObjectName(newUrl.toString());
  for (int i=0; i<children().count(); i++){
    qobject_cast<DBObjectItem*>(children().at(i))->setParentUrl(newUrl);
  }
}

QString DBObjectItem::driverName()
{
  return _driverName;
}

void DBObjectItem::deleteChildren()
{
  foreach(DBObjectItem* childItem, findChildren<DBObjectItem*>(QString(), Qt::FindDirectChildrenOnly)){
    childItem->setParent(nullptr);
    delete childItem;
  }
}

AppUrl DBObjectItem::objectUrl()
{
  AppUrl url = _parentUrl;
  QString caption = fieldValue(F_CAPTION).toString().toLower().replace(" ", "_");
  url.cd(caption);
  return url;
}

QStringList DBObjectItem::propertyList()
{
  QStringList resList = QStringList();
  for(int i=LAbstractTreeItem::staticMetaObject.propertyOffset(); i<metaObject()->propertyCount(); i++){
    resList << metaObject()->property(i).name();
  }
  return resList;
}

int DBObjectItem::fieldIndex(QString fieldName)
{
  for(int i=0; i<fields.count(); i++){
    if (fields.at(i).name == fieldName)
      return i;
  }
  return -1;
}

QString DBObjectItem::databaseName()
{
  return QSqlQueryHelper::databaseName(connectionName());
}

DBObjectField& DBObjectItem::field(QString fieldName)
{
  return fields[fieldIndex(fieldName)];
}

QString DBObjectItem::fillSqlPattern(QString pattern)
{
  foreach(DBObjectField field, fields) {
    this->setProperty(qPrintable(field.name), field.value());
  }
  return QSqlQueryHelper::fillSqlPattern(pattern, this);
}

QString DBObjectItem::fillSqlPattern(QString pattern, QMap<QString, QString> valueMap)
{
  QString result = pattern;
  foreach(QString key, valueMap.keys()) {
    result = result.replace("#" + key + "#", valueMap.value(key));
  }
  return result;
}

QString DBObjectItem::fillPatternWithFields(QString pattern)
{
  QString result = pattern;
  foreach(DBObjectField field, fields) {
    result = result.replace("#" + field.name + ".new#", field.value().toString());
    result = result.replace("#" + field.name + ".old#", field.oldValue().toString());
    result = result.replace("#" + field.name + "#", field.value().toString());
  }
  result = result.replace("#databaseName#", databaseName());
  return result;
}

QString DBObjectItem::fillWithModifiedFields(QString pattern)
{
  pattern = filterUnmodifiedFields(pattern);
  return fillPatternWithFields(pattern);
}

QString DBObjectItem::filterUnmodifiedFields(QString pattern)
{
  QString resSql;
  QStringList parts = pattern.split(QRegExp("[\\{\\}]"), QString::SkipEmptyParts);
  QRegExp rxParam("#([A-Za-z_]+)#");
  foreach(QString part, parts) {
    int paramIdx = 0;
    bool include = true;
    while (rxParam.indexIn(part, paramIdx) >= 0) {
      QString paramName = rxParam.cap(1);
      if (!fieldModified(paramName)) {
        include = false;
        break;
      }
      paramIdx += rxParam.pos() + rxParam.matchedLength();
    }
    if (include)
      resSql.append(part);
  }
  return resSql;
}

ActionResult DBObjectItem::execSql(QString sql, QString connectionName)
{
  QSqlQuery query = QSqlQueryHelper::execSql(sql, connectionName);
  if (query.lastError().isValid()) {
    return ActionResult(ERR_QUERY_ERROR, query.lastError().databaseText());
  }
  else {
    return ActionResult(RES_OK_CODE);
  }
}

QVariant DBObjectItem::fieldValue(QString fieldName)
{
  int index = fieldIndex(fieldName);
  if (index >= 0)
    return fields[index].value();
  return QVariant();
}

QVariant DBObjectItem::fieldValue(int colNumber)
{
  if (colNumber >= fields.count())
    return QVariant();
  return fields.at(colNumber).value();
}

QVariant DBObjectItem::fieldOldValue(QString fieldName)
{
  int index = fieldIndex(fieldName);
  if (index >= 0)
    return fields[index].oldValue();
  return QVariant();
}

QVariant DBObjectItem::fieldOldValue(int colIdx)
{
  if (colIdx >= fields.count())
    return QVariant();
  return fields.at(colIdx).oldValue();
}

bool DBObjectItem::fieldModified(QString fieldName)
{
  int index = fieldIndex(fieldName);
  if (index >= 0)
    return fields[index].isModified();
  return false;
}

void DBObjectItem::setFieldValue(QString fieldName, QVariant value)
{
  int index = fieldIndex(fieldName);
  if (index < 0)
    return;
  fields[index].setValue(value);
}

void DBObjectItem::setFieldValue(int colNumber, QVariant value)
{
  if (colNumber >= fields.count())
    return;
  fields[colNumber].setValue(value);
}

bool DBObjectItem::setData(int column, QVariant value, int role)
{
  if (column >= colCount())
    return false;

  if (role == Qt::EditRole){
    fields[column].setValue(value);
  }
  return true;
}

bool DBObjectItem::refresh()
{
  return true;
}

int DBObjectItem::colCount()
{
  return fields.count();
}

QVariant DBObjectItem::colData(int column, int role)
{
  if (column >= colCount())
    return QVariant();
  if ((role == Qt::DisplayRole) || (role == Qt::EditRole)){
    return fieldValue(column);
  }
  return QVariant();
}

ActionResult DBObjectItem::insertMe(){
  return ActionResult(ERR_NOT_IMPLEMENTED);
}

ActionResult DBObjectItem::updateMe()
{
  return ActionResult(ERR_NOT_IMPLEMENTED);
}

ActionResult DBObjectItem::deleteMe()
{    
  return ActionResult(ERR_NOT_IMPLEMENTED);
}

bool DBObjectItem::isEditable()
{
  return _editable;
}

bool DBObjectItem::isModified()
{
  foreach (DBObjectField field, fields) {
    if (field.isModified())
      return true;
  }
  return false;
}

bool DBObjectItem::submit()
{
  for(int i=0; i<fields.count(); i++) {
    fields[i].submit();
  }
  return true;
}

bool DBObjectItem::hasField(QString fieldName)
{
  foreach(DBObjectField field, fields) {
    if (field.name == fieldName)
      return true;
  }
  return false;
}

DBObjectField::DBObjectField(QString fieldName)
{
  name = fieldName;
}

void DBObjectItem::registerField(QString fieldName)
{
  Q_ASSERT(!hasField(fieldName)); //Doubles are forbidden
  fields.append(DBObjectField(fieldName));
}

QVariant DBObjectField::value() const
{
  return _value;
}

void DBObjectField::setValue(const QVariant &value)
{
  if (!_oldValue.isValid())
    _oldValue = _value;
  _value = value;
}

QVariant DBObjectField::oldValue() const
{
  return _oldValue;
}

bool DBObjectField::isModified()
{
  return _oldValue != _value;
}

void DBObjectField::submit()
{
  _oldValue = _value;
}

void DBObjectField::revert()
{
  _value = _oldValue;
}

ActionResult::ActionResult(int code, QString description)
{
  _resultCode = code;
  _description = description;
}

bool ActionResult::isSuccess()
{
  return _resultCode == RES_OK_CODE;
}

int ActionResult::resCode()
{
  return _resultCode;
}

QString ActionResult::description()
{
  return _description;
}
