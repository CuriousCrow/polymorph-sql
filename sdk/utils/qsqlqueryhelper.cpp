#include "qsqlqueryhelper.h"
#include <QMetaProperty>
#include <QRegularExpression>
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
  qDebug() << QString("SQL(%1): %2").arg(connectionName, sql);
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
  return dbCon.isValid() ? dbCon.databaseName() : "";
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

QString QSqlQueryHelper::fillSqlPatternByProps(QString pattern, const QObject *object)
{
  QString resSql;
  QStringList parts = pattern.split(QRegularExpression("[\\{\\}]"), Qt::SkipEmptyParts);
  QRegularExpression rxParam = QRegularExpression("#([A-Za-z_]+)#");
  foreach(QString sqlPart, parts) {
    bool include = true;
    for(const QRegularExpressionMatch &match : rxParam.globalMatch(sqlPart)) {
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
  for(const QRegularExpressionMatch &match : rxParam.globalMatch(pattern)) {
      fields.append(match.captured(1));
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

