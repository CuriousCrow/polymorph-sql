#include "dbview.h"
#include <QIcon>
#include "utils/sqlqueryhelper.h"
#include "appconst.h"


DBViewItem::DBViewItem():
  DBSelectableItem("", nullptr)
{
  _editable = false;
  registerField(F_QUERY_TEXT);
}

DBViewItem::~DBViewItem()
{
}

int DBViewItem::colCount() const
{
  return 2;
}

QVariant DBViewItem::colData(int column, int role) const
{

  switch (role) {
  case Qt::DisplayRole:
  case Qt::EditRole:
    switch (column) {
    case 0:
      return caption();
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

int DBViewItem::type() const
{
  return View;
}

ActionResult DBViewItem::insertMe()
{
  qDebug() << "Connection name" << connectionName();
  return execSql(toDDL(), connectionName());
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
  return execSql(dropDDL(), connectionName());
}

QString DBViewItem::toDDL() const
{
  QString sql = "create view %1 as #queryText#";
  QString preparedSql = fillSqlPatternWithFields(sql.arg(identifier()));
  return preparedSql;
}

QString DBViewItem::dropDDL() const
{
  QString sql = "drop view %1";
  return sql.arg(identifier());
}
