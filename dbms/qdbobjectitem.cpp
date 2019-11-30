#include "qdbobjectitem.h"
#include <QUrl>
#include <QDebug>

#include <QMetaProperty>
#include "qsqlqueryhelper.h"
#include "dbms/appconst.h"


QDBObjectItem::QDBObjectItem(QString caption, QObject* parent):
  LAbstractTreeItem(caption, parent)
{
  registerField(F_CAPTION);
  setFieldValue(F_CAPTION, caption);
}

QDBObjectItem::~QDBObjectItem()
{
}

void QDBObjectItem::setParentUrl(const QUrl &url)
{
  _parentUrl = url;
  QUrl newUrl = objectUrl();
  _connectionName = newUrl.host();
  _driverName = newUrl.scheme();
  setObjectName(newUrl.url());
  for (int i=0; i<children().count(); i++){
    qobject_cast<QDBObjectItem*>(children().at(i))->setParentUrl(newUrl);
  }
}

QString QDBObjectItem::driverName()
{
  return _driverName;
}

void QDBObjectItem::deleteChildren()
{
  foreach(QDBObjectItem* childItem, findChildren<QDBObjectItem*>(QString(), Qt::FindDirectChildrenOnly)){
    childItem->setParent(nullptr);
    delete childItem;
  }
}

QUrl QDBObjectItem::objectUrl()
{
  QUrl url = _parentUrl;
  QString path = url.path() + "/" + fieldValue(F_CAPTION).toString().toLower().replace(" ", "_");
  url.setPath(path);
  return url;
}

QStringList QDBObjectItem::propertyList()
{
  QStringList resList = QStringList();
  for(int i=LAbstractTreeItem::staticMetaObject.propertyOffset(); i<metaObject()->propertyCount(); i++){
    resList << metaObject()->property(i).name();
  }
  return resList;
}

int QDBObjectItem::fieldIndex(QString fieldName)
{
  for(int i=0; i<fields.count(); i++){
    if (fields.at(i).name == fieldName)
      return i;
  }
  return -1;
}

QString QDBObjectItem::databaseName()
{
  return QSqlQueryHelper::databaseName(connectionName());
}

QDBObjectField QDBObjectItem::field(QString fieldName)
{
  return fields.at(fieldIndex(fieldName));
}

QString QDBObjectItem::fillSqlPattern(QString pattern)
{
  foreach(QDBObjectField field, fields) {
    this->setProperty(qPrintable(field.name), field.value());
  }
  return QSqlQueryHelper::fillSqlPattern(pattern, this);
}

QString QDBObjectItem::fillSqlPattern(QString pattern, QMap<QString, QString> valueMap)
{
  QString result = pattern;
  foreach(QString key, valueMap.keys()) {
    result = result.replace("#" + key + "#", valueMap.value(key));
  }
  return result;
}

QString QDBObjectItem::fillPatternWithFields(QString pattern)
{
  QString result = pattern;
  foreach(QDBObjectField field, fields) {
    result = result.replace("#" + field.name + ".new#", field.value().toString());
    result = result.replace("#" + field.name + ".old#", field.oldValue().toString());
    result = result.replace("#" + field.name + "#", field.value().toString());
  }
  result = result.replace("#databaseName#", databaseName());
  return result;
}

QString QDBObjectItem::fillWithModifiedFields(QString pattern)
{
  pattern = filterUnmodifiedFields(pattern);
  return fillPatternWithFields(pattern);
}

QString QDBObjectItem::filterUnmodifiedFields(QString pattern)
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

ActionResult QDBObjectItem::execSql(QString sql, QString connectionName)
{
  QSqlQuery query = QSqlQueryHelper::execSql(sql, connectionName);
  if (query.lastError().isValid()) {
    return ActionResult(ERR_QUERY_ERROR, query.lastError().databaseText());
  }
  else {
    return ActionResult(RES_OK_CODE);
  }
}

QVariant QDBObjectItem::fieldValue(QString fieldName)
{
  int index = fieldIndex(fieldName);
  if (index >= 0)
    return fields[index].value();
  return QVariant();
}

QVariant QDBObjectItem::fieldValue(int colNumber)
{
  if (colNumber >= fields.count())
    return QVariant();
  return fields.at(colNumber).value();
}

QVariant QDBObjectItem::fieldOldValue(QString fieldName)
{
  int index = fieldIndex(fieldName);
  if (index >= 0)
    return fields[index].oldValue();
  return QVariant();
}

QVariant QDBObjectItem::fieldOldValue(int colIdx)
{
  if (colIdx >= fields.count())
    return QVariant();
  return fields.at(colIdx).oldValue();
}

bool QDBObjectItem::fieldModified(QString fieldName)
{
  int index = fieldIndex(fieldName);
  if (index >= 0)
    return fields[index].isModified();
  return false;
}

void QDBObjectItem::setFieldValue(QString fieldName, QVariant value)
{
  int index = fieldIndex(fieldName);
  if (index < 0)
    return;
  fields[index].setValue(value);
}

void QDBObjectItem::setFieldValue(int colNumber, QVariant value)
{
  if (colNumber >= fields.count())
    return;
  fields[colNumber].setValue(value);
}

bool QDBObjectItem::setData(int column, QVariant value, int role)
{
  if (column >= colCount())
    return false;

  if (role == Qt::EditRole){
    fields[column].setValue(value);
  }
  return true;
}

bool QDBObjectItem::refresh()
{
  return true;
}

int QDBObjectItem::colCount()
{
  return fields.count();
}

QVariant QDBObjectItem::colData(int column, int role)
{
  if (column >= colCount())
    return QVariant();
  if ((role == Qt::DisplayRole) || (role == Qt::EditRole)){
    return fieldValue(column);
  }
  return QVariant();
}

ActionResult QDBObjectItem::insertMe(){
  return ActionResult(ERR_NOT_IMPLEMENTED);
}

ActionResult QDBObjectItem::updateMe()
{
  return ActionResult(ERR_NOT_IMPLEMENTED);
}

ActionResult QDBObjectItem::deleteMe()
{    
  return ActionResult(ERR_NOT_IMPLEMENTED);
}

bool QDBObjectItem::isEditable()
{
  return _editable;
}

bool QDBObjectItem::isModified()
{
  foreach (QDBObjectField field, fields) {
    if (field.isModified())
      return true;
  }
  return false;
}

bool QDBObjectItem::submit()
{
  for(int i=0; i<fields.count(); i++) {
    fields[i].submit();
  }
  return true;
}

bool QDBObjectItem::hasField(QString fieldName)
{
  foreach(QDBObjectField field, fields) {
    if (field.name == fieldName)
      return true;
  }
  return false;
}

QDBObjectField::QDBObjectField(QString fieldName)
{
  name = fieldName;
}

void QDBObjectItem::registerField(QString fieldName)
{
  Q_ASSERT(!hasField(fieldName)); //Doubles are forbidden
  fields.append(QDBObjectField(fieldName));
}

QVariant QDBObjectField::value() const
{
  return _value;
}

void QDBObjectField::setValue(const QVariant &value)
{
  if (!_oldValue.isValid())
    _oldValue = _value;
  _value = value;
}

QVariant QDBObjectField::oldValue() const
{
  return _oldValue;
}

bool QDBObjectField::isModified()
{
  return _oldValue != _value;
}

void QDBObjectField::submit()
{
  _oldValue = _value;
}

void QDBObjectField::revert()
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
