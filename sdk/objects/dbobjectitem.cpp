#include "dbobjectitem.h"
#include <QDebug>

#include <QMetaProperty>
#include <QRegularExpression>
#include "utils/sqlqueryhelper.h"
#include "appconst.h"


DBObjectItem::DBObjectItem(QString caption, QObject* parent):
  LAbstractTreeItem(caption, parent)
{
  _identifierSupport = new NoOpIdentifier();

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

void DBObjectItem::updateUrl()
{
  AppUrl newUrl = objectUrl();
  _connectionName = newUrl.connection();
  _driverName = newUrl.driver();
  setObjectName(newUrl.toString());
  for (int i=0; i<children().count(); i++){
    static_cast<DBObjectItem*>(children().at(i))->setParentUrl(newUrl);
  }
}

void DBObjectItem::setParentUrl(const AppUrl &url)
{
  _parentUrl = url;
  updateUrl();
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
    DBObjectItem* child = static_cast<DBObjectItem*>(children().at(idx));
    if (child->type() == type && (name.isEmpty() || child->caption() == name))
      return child;
  }
  return nullptr;
}

AppUrl DBObjectItem::objectUrl()
{
  AppUrl url = _parentUrl;
  QString caption = fieldValue(F_CAPTION).toString().replace(" ", "_");
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
  return SqlQueryHelper::databaseName(connectionName());
}

DBObjectField& DBObjectItem::field(QString fieldName)
{
  return fields[fieldIndex(fieldName)];
}

QString DBObjectItem::identifier() const
{
  return _identifierSupport->escapeIdentifier(caption());
}

QString DBObjectItem::fillSqlPatternWithFields(QString pattern, QMap<QString, QString> valueMap) const
{
  QString result = pattern;
  QMapIterator<QString, QString> it(valueMap);
  while(it.hasNext()) {
    it.next();
    result = result.replace("#" + it.key() + "#", it.value());
  }
  return result;
}

QString DBObjectItem::fillSqlPatternWithFields(QString pattern) const
{
  QString result = pattern;
  foreach(DBObjectField field, fields) {
    result = result.replace("#" + field.name + ".new#", varToStr(field.value()));
    result = result.replace("#" + field.name + ".old#", varToStr(field.oldValue()));
    result = result.replace("#" + field.name + "#", varToStr(field.value()));
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
  return fillSqlPatternWithFields(pattern);
}

QString DBObjectItem::filterUnmodifiedFields(QString pattern) const
{
  QString resSql;
  QStringList parts = pattern.split(QRegularExpression("[\\{\\}]"), Qt::SkipEmptyParts);
  QRegularExpression rxParam("#([A-Za-z_]+)#");
  foreach(QString part, parts) {
    bool include = true;

    QRegularExpressionMatchIterator i = rxParam.globalMatch(part);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
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
  QSqlQuery query = SqlQueryHelper::execSql(sql, connectionName);
  if (query.lastError().isValid()) {
    return ActionResult(ERR_QUERY_ERROR, query.lastError().databaseText());
  }
  else {
    return RES_OK_CODE;
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

void DBObjectItem::copyFieldTo(QString fieldName, DBObjectItem *targetObj)
{
    targetObj->setFieldValue(fieldName, fieldValue(fieldName));
}

void DBObjectItem::copyFieldsTo(DBObjectItem *targetObj)
{
    foreach(DBObjectField field, fields) {
        targetObj->setFieldValue(field.name, field.value());
    }
}

QString DBObjectItem::baseClassByType(DBObjectItem::ItemType type)
{
    switch (type) {
    case DBObjectItem::Database:
        return "DBDatabaseItem";
    case DBObjectItem::Table:
        return "DBTableItem";
    case DBObjectItem::View:
        return "DBViewItem";
    case DBObjectItem::Sequence:
        return "DBSequenceItem";
    case DBObjectItem::Procedure:
        return "DBProcedureItem";
    case DBObjectItem::Folder:
        return "DBFolderItem";
    case DBObjectItem::Trigger:
        return "DBTriggerItem";
    case DBObjectItem::PrimaryKey:
        return "DBPrimaryKey";
    case DBObjectItem::ForeignKey:
        return "DBForeignKey";
    case DBObjectItem::UniqueConstraint:
        return "DBUniqueConstraint";
    case DBObjectItem::CheckConstraint:
        return "DBCheckConstraint";
    case DBObjectItem::SystemTable:
        return "DBTableItem";
    default:
        return "DBObjectItem";
    }
}

void DBObjectItem::setFieldValue(int colNumber, QVariant value)
{
  if (colNumber >= fields.count()) {
    qWarning() << "setFieldValue(): Invalid field index " << colNumber;
    return;
  }
  fields[colNumber].setValue(value);
}

QString DBObjectItem::varToStr(QVariant variant) const
{
  if (variant.isNull()) {
    return "null";
  }
  else {
    return variant.toString();
  }
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

bool DBObjectItem::revert()
{
  for(int i=0; i<fields.count(); i++) {
    fields[i].revert();
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
