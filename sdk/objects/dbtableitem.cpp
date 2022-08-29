#include "dbtableitem.h"
#include "appurl.h"
#include <QIcon>
#include "utils/sqlqueryhelper.h"
#include <QSqlField>
#include <QSqlRecord>
#include "appconst.h"


DBTableItem::DBTableItem():
  DBSelectableItem("", nullptr)
{      
}

DBTableItem::~DBTableItem()
{
}

void DBTableItem::reloadColumnsModel()
{
  //Must be overrided for single one DBMS
}

void DBTableItem::reloadConstraintsModel()
{
  //Must be overrided for single one DBMS
}

SqlColumnModel *DBTableItem::columnsModel()
{
  return _columnsModel;
}

QAbstractTableModel *DBTableItem::constraintsModel()
{
  return _constraintsModel;
}

DBForeignKey *DBTableItem::newForeignKey()
{
  return new DBForeignKey("fk_" + caption());
}

DBPrimaryKey *DBTableItem::newPrimaryKey()
{
  return new DBPrimaryKey("pk_" + caption());
}

DBUniqueConstraint *DBTableItem::newUniqueConstraint()
{
  return new DBUniqueConstraint("uq_" + caption());
}

DBCheckConstraint *DBTableItem::newCheckConstraint()
{
  return new DBCheckConstraint("chk_" + caption());
}

void DBTableItem::addDefaultColumn()
{  
  int newColNumber = 1;
  forever {
    if (_columnsModel->rowByName(DEF_COLUMN_NAME + QString::number(newColNumber)) < 0)
      break;
    newColNumber++;
  }
  _columnsModel->addSqlColumn(SqlColumn(DEF_COLUMN_NAME + QString::number(newColNumber), NoType));
}

void DBTableItem::setSystem(bool system)
{
  _isSystem = system;
  _editable = !_isSystem;
}

ActionResult DBTableItem::deleteMe()
{
  QString sql = "drop table %1";
  QString preparedSql = sql.arg(identifier());
  return execSql(preparedSql, connectionName());
}

bool DBTableItem::refresh()
{
  reloadColumnsModel();
  reloadConstraintsModel();
  submit();
  return true;
}

bool DBTableItem::isModified() const
{
  if (DBObjectItem::isModified())
    return true;
  return _columnsModel->isModified();
}

DBForeignKey *DBTableItem::loadForeignKey(QString name)
{
  DBForeignKey* foreignKey = newForeignKey();
  foreignKey->setFieldValue(F_CAPTION, name);
  foreignKey->setFieldValue(F_TABLE, this->caption());
  foreignKey->setParentUrl(this->objectUrl());
  foreignKey->refresh();
  return foreignKey;
}

ActionResult DBTableItem::updateMe()
{
  SqlColumnModel::EditType editType = _columnsModel->editType();
  if (editType == SqlColumnModel::DropTable) {
    return deleteMe();
  }
  else if (editType == SqlColumnModel::CreateTable) {
    return insertMe();
  }
  else {
    if (editType == SqlColumnModel::NoChanges && !isModified()) {
      qDebug() << "No changes";
      return ActionResult();
    }
    //    qDebug() << "Table" << fieldValue("caption").toString() << "modified";
    //    qDebug() << _columnsModel->columnChanges();
    return ActionResult(RES_BASE_ERROR, tr("Once returned 'false'. Should be verified"));
  }
}

int DBTableItem::type() const
{
  return _isSystem ? SystemTable : Table;
}

QString DBTableItem::toDML() const
{
  QString tablename = caption();
  QString sql = "select * from %1";
  QString preparedSql = sql.arg(identifier());
  QSqlQuery result = SqlQueryHelper::execSql(preparedSql, _connectionName);
  QStringList dmlList;
  while(result.next()) {
    QString insertSql = result.driver()->sqlStatement(QSqlDriver::InsertStatement, tablename, result.record(), false);
    dmlList.append(insertSql + SQL_DELIMITER);
  }
  return dmlList.join(FILE_DELIMITER);
}
