#include "qdbtableitem.h"
#include <QUrl>
#include <QIcon>
#include "qsqlqueryhelper.h"

QDBTableItem::QDBTableItem(QString caption, QObject* parent):
  QDBObjectItem(caption, parent)
{  
}

QDBTableItem::~QDBTableItem()
{
}

bool QDBTableItem::loadChildren()
{
  return true;
}


QUrl QDBTableItem::objectUrl()
{
  QUrl url = QDBObjectItem::objectUrl();
  url.setPath("/" + fieldValue("caption").toString());
  return url;
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
      return fieldValue("caption");
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
  QString sql = "drop table #caption#";
  QString preparedSql = fillSqlPattern(sql);
  return !QSqlQueryHelper::execSql(preparedSql, connectionName()).lastError().isValid();
}

bool QDBTableItem::insertMe()
{
  return false;
}

bool QDBTableItem::updateMe()
{
  QDBObjectField captionField = fields.at(fieldIndex("caption"));
  if (captionField.isModified()) {
    QString sql = "alter table #caption.old# rename to #caption.new#";
    QString preparedSql = fillPatternWithFields(sql);
    return !QSqlQueryHelper::execSql(preparedSql, connectionName()).lastError().isValid();
  }
}


int QDBTableItem::type()
{
  return Table;
}
