#ifndef SQLQUERYHELPER_H
#define SQLQUERYHELPER_H

#include <QSqlDatabase>
#include <QSqlQuery>

#include <QSqlError>
#include <QDebug>

#define DEBUG_SQL

class SqlQueryHelper
{
public:
  SqlQueryHelper();
  ~SqlQueryHelper();
  static QSqlQuery execSql(QString sql, QString connectionName = QSqlDatabase::defaultConnection);
  static bool execSql(QSqlQuery &query);
  static QSqlQuery prepareQuery(QString sql, QString connectionName = QSqlDatabase::defaultConnection);
  static QString databaseName(QString connection);
  static QString driverName(QString connection);
  static QSqlRecord tableRowInfo(QString table, QString connectionName);
  static QString fillSqlPatternByProps(QString pattern, const QObject* object);
  static void fillObjectFromRecord(QObject* object, QSqlRecord& rec);
};

#endif // SQLQUERYHELPER_H
