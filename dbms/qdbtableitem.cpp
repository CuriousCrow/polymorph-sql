#include "qdbtableitem.h"
#include <QUrl>
#include <QIcon>
#include "qsqlqueryhelper.h"
#include <QSqlField>
#include <QSqlRecord>
#include "dbms/appconst.h"
#include "qknowledgebase.h"


QDBTableItem::QDBTableItem(QString caption, QObject* parent):
  QDBObjectItem(caption, parent)
{      
}

QDBTableItem::~QDBTableItem()
{
}

void QDBTableItem::reloadColumnsModel()
{
  //Необходимо переопределять для каждой отдельной СУБД
}

QAbstractTableModel *QDBTableItem::columnsModel()
{
  return _columnsModel;
}

int QDBTableItem::colTypeFromString(QString name)
{
  return QKnowledgeBase::kb()->typeByName(driverName(), name.toUpper());
}

void QDBTableItem::addDefaultColumn()
{  
  int newColNumber = 1;
  forever {
    if (_columnsModel->rowByName(DEF_COLUMN_NAME + QString::number(newColNumber)) < 0)
      break;
    newColNumber++;
  }
  _columnsModel->addSqlColumn(SqlColumn(DEF_COLUMN_NAME + QString::number(newColNumber), NoType));
}

bool QDBTableItem::loadChildren()
{
  return true;
}

int QDBTableItem::colCount()
{
  return 1;
}

QVariant QDBTableItem::colData(int column, int role)
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

bool QDBTableItem::deleteMe()
{
  QString sql = "drop table \"%1\"";
  QString preparedSql = sql.arg(fieldValue(F_CAPTION).toString());
  return !QSqlQueryHelper::execSql(preparedSql, connectionName()).lastError().isValid();
}

bool QDBTableItem::insertMe()
{
  return false;
}

bool QDBTableItem::updateMe()
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
      return true;
    }
    //    qDebug() << "Table" << fieldValue("caption").toString() << "modified";
    //    qDebug() << _columnsModel->columnChanges();
    return false;
  }
}


int QDBTableItem::type()
{
  return Table;
}
