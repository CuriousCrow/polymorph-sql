#include "qdbobjectitem.h"
#include <QUrl>
#include <QDebug>

#include <QMetaProperty>
#include "qsqlqueryhelper.h"


QDBObjectItem::QDBObjectItem(QString caption, QObject* parent): LAbstractTreeItem(caption, parent)
{
  registerField("caption");
  setFieldValue("caption", caption);
}

QDBObjectItem::~QDBObjectItem()
{
}

QUrl QDBObjectItem::objectUrl()
{
  if (parent() && parent()->inherits("LAbstractTreeItem"))
    return ((QDBObjectItem*)parent())->objectUrl();
  else
    return QUrl();
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
  return true;
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

void QDBObjectItem::updateObjectName()
{
  QUrl objUrl = objectUrl();
  QString newObjectName = objUrl.url();
  _connectionName = objUrl.host();
//  qDebug() << this << "connection name:" << objUrl.host();
//  qDebug() << this << "new object name:" << newObjectName;
  setObjectName(newObjectName);
  for (int i=0; i<children().count(); i++){
    qobject_cast<QDBObjectItem*>(children().at(i))->updateObjectName();
  }
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

bool QDBObjectItem::insertMe(){
  return true;
}

bool QDBObjectItem::updateMe()
{
  return true;
}

bool QDBObjectItem::deleteMe()
{    
  return true;
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

QDBObjectField::QDBObjectField(QString fieldName)
{
  name = fieldName;
}

void QDBObjectItem::registerField(QString fieldName)
{
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
