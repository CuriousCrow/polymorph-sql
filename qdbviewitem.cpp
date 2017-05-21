#include "qdbviewitem.h"
#include <QIcon>
#include "qsqlqueryhelper.h"


QDBViewItem::QDBViewItem(QString caption, QObject *parent):
  QDBTableItem(caption, parent)
{
    _editable = false;
}

QDBViewItem::~QDBViewItem()
{
}
QString QDBViewItem::queryText() const
{
  return _queryText;
}

void QDBViewItem::setQueryText(const QString &queryText)
{
  _queryText = queryText;
}

int QDBViewItem::colCount()
{
  return 2;
}

QVariant QDBViewItem::colData(int column, int role)
{

  switch (role) {
  case Qt::DisplayRole:
  case Qt::EditRole:
    switch (column) {
    case 0:
      return fieldValue("caption");
    case 1:
      return queryText();
    default:
      return QVariant();
    }
  case Qt::DecorationRole:
    return QIcon(":/icons/table.png");
  default:
    return QVariant();
  }
}

int QDBViewItem::type()
{
  return View;
}


bool QDBViewItem::setData(int column, QVariant value, int role)
{
  if (role == Qt::EditRole){
    switch (column) {
    case 0:
      setFieldValue("caption", value);
      break;
    case 1:
      setFieldValue("queryText", value);
      break;
    default:
      break;
    }
  }
  return true;
}


bool QDBViewItem::deleteMe()
{
  QString sql = "drop view #caption#";
  QString preparedSql = fillSqlPattern(sql);
  return !QSqlQueryHelper::execSql(preparedSql, connectionName()).lastError().isValid();
}
