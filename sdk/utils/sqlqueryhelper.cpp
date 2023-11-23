#include "sqlqueryhelper.h"
#include <QMetaProperty>
#include <QRegularExpression>
#include <QSqlRecord>


SqlQueryHelper::SqlQueryHelper()
{

}

SqlQueryHelper::~SqlQueryHelper()
{

}

QSqlQuery SqlQueryHelper::execSql(QString sql, QString connectionName)
{
#ifdef DEBUG_SQL
  qDebug() << QString("SQL(%1): %2").arg(connectionName, sql);
#endif
  QSqlQuery sqlResult(sql, QSqlDatabase::database(connectionName));
  auto resOk = sqlResult.exec();
#ifdef DEBUG_SQL
  if (!resOk){
    qWarning() << "Error" << sqlResult.lastError().text();
  }
#endif
  return sqlResult;
}

bool SqlQueryHelper::execSql(QSqlQuery &query)
{
  bool resOk = query.exec();
  if (true) {
    qDebug() << QString("SQL: %1").arg(query.executedQuery());
    if (!resOk)
      qWarning() << "Error:" << query.lastError().text();
  }
  return resOk;
}

QSqlQuery SqlQueryHelper::prepareQuery(QString sql,  QString connectionName)
{
  QSqlQuery query(QSqlDatabase::database(connectionName));
  bool resOk = query.prepare(sql);
  if (true && !resOk) {
    qWarning() << "Prepare error:" << query.lastError().text();
  }
  return query;
}

QString SqlQueryHelper::databaseName(QString connection)
{
  QSqlDatabase dbCon = QSqlDatabase::database(connection, false);
  return dbCon.isValid() ? dbCon.databaseName() : "";
}

QString SqlQueryHelper::driverName(QString connection)
{
  QSqlDatabase dbCon = QSqlDatabase::database(connection, false);
  Q_ASSERT(dbCon.isValid());
  return dbCon.driverName();
}

QSqlRecord SqlQueryHelper::tableRowInfo(QString table, QString connectionName)
{
  QSqlRecord rec = QSqlDatabase::database(connectionName).record(table);
  qDebug() << "Table info:" << rec;
  return rec;
}

QString SqlQueryHelper::fillSqlPatternByProps(QString pattern, const QObject *object)
{
  QString resSql;
  QStringList parts = pattern.split(QRegularExpression("[\\{\\}]"), Qt::SkipEmptyParts);
  QRegularExpression rxParam = QRegularExpression("#([A-Za-z_]+)#");
  foreach(QString sqlPart, parts) {
    bool include = true;
    QRegularExpressionMatchIterator i = rxParam.globalMatch(sqlPart);
    while(i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString paramName = match.captured(1);
        if (object->property(paramName.toUtf8()).isValid()) {
            include = false;
            break;
        }
    }
    if (include)
      resSql.append(sqlPart);
  }

  QStringList fields;
  QRegularExpressionMatchIterator i = rxParam.globalMatch(pattern);
  while(i.hasNext()) {
      QRegularExpressionMatch match = i.next();
      fields.append(match.captured(1));
  }
  fields.removeDuplicates();
  QString result(pattern);
  foreach(QString field, fields){
    result = result.replace("#"+field+"#", object->property(qPrintable(field)).toString());
  }
  return result;
}

void SqlQueryHelper::fillObjectFromRecord(QObject *object, QSqlRecord &rec)
{  
  for (int i=0; i<rec.count(); i++){

    object->setProperty(qPrintable(rec.fieldName(i)), rec.value(i));
  }
}

