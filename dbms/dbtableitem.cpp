#include "dbtableitem.h"
#include "appurl.h"
#include <QIcon>
#include "qsqlqueryhelper.h"
#include <QSqlField>
#include <QSqlRecord>
#include "dbms/appconst.h"
#include "qknowledgebase.h"


DBTableItem::DBTableItem(QString caption, QObject* parent):
  DBObjectItem(caption, parent)
{      
}

DBTableItem::~DBTableItem()
{
}

void DBTableItem::reloadColumnsModel()
{
  //Необходимо переопределять для каждой отдельной СУБД
}

void DBTableItem::reloadConstraintsModel()
{
  //Необходимо переопределить для каждой отдельной СУБД
}

QAbstractTableModel *DBTableItem::columnsModel()
{
  return _columnsModel;
}

QAbstractTableModel *DBTableItem::constraintsModel()
{
  return _constraintsModel;
}

DBForeignKey *DBTableItem::newForeignKey()
{
  return new DBForeignKey("fk_" + fieldValue(F_CAPTION).toString());
}

int DBTableItem::colTypeFromString(QString name)
{
//  qDebug() << "ColTypeFromString:" << name.toUpper();
  return QKnowledgeBase::kb()->typeByName(driverName().toUpper(), name.toUpper());
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

bool DBTableItem::reloadChildren()
{
  return true;
}

int DBTableItem::colCount()
{
  return 1;
}

QVariant DBTableItem::colData(int column, int role)
{
  switch (role) {
  case Qt::DisplayRole:
    switch (column) {
    case 0:
      return fieldValue(F_CAPTION);
    default:
      return QVariant();
    }
  case Qt::DecorationRole:
    return QIcon(":/icons/table.png");
  default:
    return QVariant();
  }
}

ActionResult DBTableItem::deleteMe()
{
  QString sql = "drop table \"%1\"";
  QString preparedSql = sql.arg(fieldValue(F_CAPTION).toString());
  return execSql(preparedSql, connectionName());
}

bool DBTableItem::isModified()
{
  if (DBObjectItem::isModified())
    return true;
  return _columnsModel->isModified();
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
    return ActionResult(RES_BASE_ERROR, "Раньше возвращалось false. Надо проверить");
  }
}


int DBTableItem::type()
{
  return Table;
}
