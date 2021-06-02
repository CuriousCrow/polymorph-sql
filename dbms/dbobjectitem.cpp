#include "dbobjectitem.h"
#include <QDebug>

#include <QMetaProperty>
#include <QRegularExpression>
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

QString DBObjectItem::connectionName() const
{
  return _connectionName;
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

QString DBObjectItem::driverName() const
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

QString DBObjectItem::caption() const
{
  return fieldValue(F_CAPTION).toString();
}

DBObjectItem *DBObjectItem::childItem(DBObjectItem::ItemType type, QString name)
{
  for(int idx=0; idx<children().count(); idx++) {
    DBObjectItem* child = qobject_cast<DBObjectItem*>(children().at(idx));
    if (child->type() == type && (name.isEmpty() || child->caption() == name))
      return child;
  }
  return nullptr;
}

AppUrl DBObjectItem::objectUrl()
{
  AppUrl url = _parentUrl;
  QString caption = fieldValue(F_CAPTION).toString().toLower().replace(" ", "_");
  url.cd(caption);
  return url;
}

int DBObjectItem::fieldIndex(QString fieldName) const
{
  for(int i=0; i<fields.count(); i++){
    if (fields.at(i).name == fieldName)
      return i;
  }
  return -1;
}

QString DBObjectItem::databaseName() const
{
  return QSqlQueryHelper::databaseName(connectionName());
}

DBObjectField& DBObjectItem::field(QString fieldName)
{
  return fields[fieldIndex(fieldName)];
}

//TODO: Пробная замена на вызов fillPatternWithFields. Если ничего не сломается, можно будет заменить одним методом
QString DBObjectItem::fillSqlPattern(QString pattern) const
{
    return fillPatternWithFields(pattern);
}

QString DBObjectItem::fillSqlPattern(QString pattern, QMap<QString, QString> valueMap) const
{
  QString result = pattern;
  foreach(QString key, valueMap.keys()) {
    result = result.replace("#" + key + "#", valueMap.value(key));
  }
  return result;
}

QString DBObjectItem::fillPatternWithFields(QString pattern) const
{
  QString result = pattern;
  foreach(DBObjectField field, fields) {
    result = result.replace("#" + field.name + ".new#", field.value().toString());
    result = result.replace("#" + field.name + ".old#", field.oldValue().toString());
    result = result.replace("#" + field.name + "#", field.value().toString());
  }
  //Only for already existing objects
  if (!_connectionName.isEmpty()) {
    result = result.replace("#databaseName#", databaseName());
  }
  return result;
}

QString DBObjectItem::fillWithModifiedFields(QString pattern) const
{
  pattern = filterUnmodifiedFields(pattern);
  return fillPatternWithFields(pattern);
}

QString DBObjectItem::filterUnmodifiedFields(QString pattern) const
{
  QString resSql;
  QStringList parts = pattern.split(QRegularExpression("[\\{\\}]"), Qt::SkipEmptyParts);
  QRegularExpression rxParam("#([A-Za-z_]+)#");
  foreach(QString part, parts) {
    bool include = true;

    for (QRegularExpressionMatch match : rxParam.globalMatch(part)) {
        QString paramName = match.captured(1);
        if (!fieldModified(paramName)) {
            include = false;
            break;
        }
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

QVariant DBObjectItem::fieldValue(QString fieldName) const
{
  int index = fieldIndex(fieldName);
  if (index >= 0)
    return fields[index].value();
  return QVariant();
}

QVariant DBObjectItem::fieldValue(int colNumber) const
{
  if (colNumber >= fields.count())
    return QVariant();
  return fields.at(colNumber).value();
}

QVariant DBObjectItem::fieldOldValue(QString fieldName) const
{
  int index = fieldIndex(fieldName);
  if (index >= 0)
    return fields[index].oldValue();
  return QVariant();
}

QVariant DBObjectItem::fieldOldValue(int colIdx) const
{
  if (colIdx >= fields.count())
    return QVariant();
  return fields.at(colIdx).oldValue();
}

bool DBObjectItem::fieldModified(QString fieldName) const
{
  int index = fieldIndex(fieldName);
  if (index >= 0)
    return fields[index].isModified();
  return false;
}

void DBObjectItem::setFieldValue(QString fieldName, QVariant value)
{
  int index = fieldIndex(fieldName);
  if (index < 0) {
    qWarning() << "setFieldValue(): Field not found " << fieldName;
    return;
  }
  setFieldValue(index, value);
}

void DBObjectItem::setFieldValue(int colNumber, QVariant value)
{
  if (colNumber >= fields.count()) {
    qWarning() << "setFieldValue(): Invalid field index " << colNumber;
    return;
  }
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

QString DBObjectItem::toDDL() const
{
  return "";
}

QString DBObjectItem::toDML() const
{
  return "";
}

int DBObjectItem::colCount() const
{
  return fields.count();
}

QVariant DBObjectItem::colData(int column, int role) const
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

bool DBObjectItem::isEditable() const
{
  return _editable;
}

bool DBObjectItem::isModified() const
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

bool DBObjectItem::hasField(QString fieldName) const
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

bool DBObjectField::isModified() const
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

bool ActionResult::isSuccess() const
{
  return _resultCode == RES_OK_CODE;
}

int ActionResult::resCode() const
{
  return _resultCode;
}

QString ActionResult::description() const
{
  return _description;
}
