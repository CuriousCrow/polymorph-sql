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

bool QSqlQueryHelper::execSql(QSqlQuery &query)
{
  bool resOk = query.exec();
  if (true) {
    qDebug() << QString("SQL: %1").arg(query.executedQuery());
    if (!resOk)
      qWarning() << "Error:" << query.lastError().text();
  }
  return resOk;
}

QSqlQuery QSqlQueryHelper::prepareQuery(QString sql,  QString connectionName)
{
  QSqlQuery query(QSqlDatabase::database(connectionName));
  bool resOk = query.prepare(sql);
  if (true && !resOk) {
    qWarning() << "Prepare error:" << query.lastError().text();
  }
  return query;
}

QString QSqlQueryHelper::databaseName(QString connection)
{
  QSqlDatabase dbCon = QSqlDatabase::database(connection, false);
  Q_ASSERT(dbCon.isValid());
  return dbCon.databaseName();
}

QString QSqlQueryHelper::driverName(QString connection)
{
  QSqlDatabase dbCon = QSqlDatabase::database(connection, false);
  Q_ASSERT(dbCon.isValid());
  return dbCon.driverName();
}

QSqlRecord QSqlQueryHelper::tableRowInfo(QString table, QString connectionName)
{
  QSqlRecord rec = QSqlDatabase::database(connectionName).record(table);
  qDebug() << "Table info:" << rec;
  return rec;
}


QStringList QSqlQueryHelper::propertyList(const QMetaObject *metaObj)
{
  QStringList resList = QStringList();
  for(int i=LAbstractTreeItem::staticMetaObject.propertyOffset(); i<metaObj->propertyCount(); i++){
    resList << metaObj->property(i).name();
  }
  return resList;
}

QString QSqlQueryHelper::fillSqlPattern(QString pattern, const QObject *object)
{
  QString resSql;
  QStringList parts = pattern.split(QRegExp("[\\{\\}]"), QString::SkipEmptyParts);
  QRegExp rxParam = QRegExp("#([A-Za-z_]+)#");
  foreach(QString sqlPart, parts) {
    int paramIdx = 0;
    bool include = true;
    while (rxParam.indexIn(sqlPart, paramIdx) >= 0) {
      QString paramName = rxParam.cap(1);
      if (object->property(paramName.toUtf8()).isValid()) {
        include = false;
        break;
      }
      paramIdx += rxParam.pos() + rxParam.matchedLength();
    }
    if (include)
      resSql.append(sqlPart);
  }

  QStringList fields;
  int index = 0;
  while (index >= 0){
    index = rxParam.indexIn(pattern, index);
    if (index >= 0){
      fields.append(rxParam.cap(1));
      index += rxParam.cap().length();
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

