#include "qsqlqueryhelper.h"
#include <QMetaProperty>
#include <QRegExp>
#include <QSqlRecord>
#include "lstandardtreemodel.h"

QSqlQueryHelper::QSqlQueryHelper()
{

}

QSqlQueryHelper::~QSqlQueryHelper()
{

}

QSqlQuery QSqlQueryHelper::execSql(QString sql, QString connectionName)
{
#ifdef DEBUG_SQL
  qDebug() << QString("SQL(%1): %2").arg(connectionName).arg(sql);
#endif
  QSqlQuery sqlResult = QSqlDatabase::database(connectionName).exec(sql);
#ifdef DEBUG_SQL
  if (sqlResult.lastError().isValid()){
    qWarning() << "Error" << sqlResult.lastError().text();
  }
#endif
  return sqlResult;
}

QStringList QSqlQueryHelper::propertyList(const QMetaObject *metaObj)
{
  QStringList resList = QStringList();
  for(int i=LAbstractTreeItem::staticMetaObject.propertyOffset(); i<metaObj->propertyCount(); i++){
    resList << metaObj->property(i).name();
  }
  return resList;
}

QString QSqlQueryHelper::fillSqlPattern(QString pattern, QObject *object)
{
  QRegExp rx = QRegExp("#([A-Za-z]+)#");
  QStringList fields;
  int index = 0;
  while (index >= 0){
    index = rx.indexIn(pattern, index);
    if (index >= 0){
      fields.append(rx.cap(1));
      index += rx.cap().length();
    }
  }
  fields.removeDuplicates();
  QString result(pattern);
  foreach(QString field, fields){
    result = result.replace("#"+field+"#", object->property(qPrintable(field)).toString());
  }
  return result;
}

void QSqlQueryHelper::fillObjectFromRecord(QObject *object, QSqlRecord &rec)
{
  for (int i=0; i<rec.count(); i++){
    object->setProperty(qPrintable(rec.fieldName(i)), rec.value(i));
  }
}

