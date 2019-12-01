#include "dbviewitem.h"
#include <QIcon>
#include "qsqlqueryhelper.h"
#include "dbms/appconst.h"


DBViewItem::DBViewItem(QString caption, QObject *parent):
  DBTableItem(caption, parent)
{
  _editable = false;
  registerField(F_QUERY_TEXT);
}

DBViewItem::~DBViewItem()
{
}

int DBViewItem::colCount()
{
  return 2;
}

QVariant DBViewItem::colData(int column, int role)
{

  switch (role) {
  case Qt::DisplayRole:
  case Qt::EditRole:
    switch (column) {
    case 0:
      return fieldValue(F_CAPTION);
    case 1:
      return fieldValue(F_QUERY_TEXT);
    default:
      return QVariant();
    }
  case Qt::DecorationRole:
    return QIcon(":/icons/table.png");
  default:
    return QVariant();
  }
}

int DBViewItem::type()
{
  return View;
}

ActionResult DBViewItem::insertMe()
{
  qDebug() << "Connection name" << connectionName();
  QString sql = "create view \"#caption#\" as #queryText#";
  QString preparedSql = fillSqlPattern(sql);
  return execSql(preparedSql, connectionName());
}


bool DBViewItem::setData(int column, QVariant value, int role)
{
  if (role == Qt::EditRole){
    switch (column) {
    case 0:
      setFieldValue(F_CAPTION, value);
      break;
    case 1:
      setFieldValue(F_QUERY_TEXT, value);
      break;
    default:
      break;
    }
  }
  return true;
}


ActionResult DBViewItem::deleteMe()
{
  QString sql = "drop view \"#caption#\"";
  QString preparedSql = fillSqlPattern(sql);
  return execSql(preparedSql, connectionName());
}