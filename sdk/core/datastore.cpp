#include "datastore.h"
#include "appsettings.h"
#include <QMessageBox>
#include <QDebug>
#include <QApplication>
#include <QSqlRecord>
#include "objects/appconst.h"
#include "utils/sqlqueryhelper.h"
#include "core.h"


DataStore::DataStore(QObject *parent) : QObject(parent)
{
  qDebug() << QSqlDatabase::drivers();
  //Connection to properies DB
  appDB = QSqlDatabase::addDatabase(DRIVER_SQLITE);
  QString dbPath = AppSettings::strVal(PRM_DATABASE, "properties.sqlite");
  qDebug() << "dbPath:" << dbPath;
  appDB.setDatabaseName(dbPath);

  //Trying to connect
  if (!appDB.open()){
    qCritical() << appDB.lastError().text();
    QApplication::quit();
  }
  qDebug() << "Success!";

  _structureModel = new LStructureItemModel(this);

  //Query history model (one for all databases)
  _queryHistoryModel = new UniSqlTableModel(this);
  _queryHistoryModel->setTable("t_query_history");
  _queryHistoryModel->orderBy(F_ID, Qt::DescendingOrder);
}

void DataStore::setTabWidget(QTabWidget *tabWidget)
{
  _tabWidget = tabWidget;
}

QTabWidget *DataStore::tabWidget()
{
  return _tabWidget;
}

void DataStore::initRegisteredDatabases()
{
  QString sql = "select id id, name caption, driver driverName, local_path databaseName, "
                "host_address hostName, username userName, password password, port port from t_database";
  QSqlQuery sqlResult = SqlQueryHelper::execSql(sql);
  while (sqlResult.next()) {
    QSqlRecord rec = sqlResult.record();
    QString driverName = rec.value(F_DRIVER_NAME).toString();
    IocPlugin* plugin = Core::plugin(driverName, FeatureType::DbmsObjects);
    if (!plugin) {
      qWarning() << "Can't load dbms plugin:" << driverName;
      continue;
    }
    DBDatabaseItem* item = Core::instance()->dependencyForDriver<DBDatabaseItem>(driverName);
    for (int i=0; i<rec.count(); i++) {
      item->setFieldValue(rec.fieldName(i), rec.value(i));
    }
    _structureModel->appendItem(item);
  }
  return;
}

LStructureItemModel *DataStore::structureModel()
{
  return _structureModel;
}

QModelIndex DataStore::itemIdx(DBObjectItem *fromItem, QString folder, QString name)
{
  AppUrl folderUrl = fromItem->objectUrl().folderUrl(folder);
  if (!name.isEmpty())
    folderUrl.cd(name);
  return structureModel()->indexByUrl(folderUrl);
}

DBObjectItem *DataStore::itemByFolderAndName(DBObjectItem *fromItem, QString folder, QString name)
{
  AppUrl folderUrl = fromItem->objectUrl().folderUrl(folder);
  if (!name.isEmpty())
    folderUrl.cd(name);
  return structureModel()->itemByUrl(folderUrl);
}

DBDatabaseItem *DataStore::databaseItem(DBObjectItem *item)
{
  AppUrl itemUrl = item->objectUrl();
  AppUrl dbUrl(itemUrl.driver(), itemUrl.database());
  return static_cast<DBDatabaseItem*>(structureModel()->itemByUrl(dbUrl));
}

int DataStore::databaseIdFromItem(DBObjectItem *item)
{
  DBObjectItem* curItem = item;
  while(curItem && curItem->type() != DBObjectItem::Database) {
      curItem = static_cast<DBObjectItem*>(curItem->parent());
  }
  return curItem ? curItem->fieldValue(F_ID).toInt() : -1;
}

UniSqlTableModel *DataStore::historyModel(int dbId)
{
  _queryHistoryModel->filter()->clear();
  _queryHistoryModel->filter()->addEqualFilter(F_DATABASE_ID, dbId);
  _queryHistoryModel->select();
  return _queryHistoryModel;
}

QByteArray DataStore::loadTableState(int dbId, QString name)
{
  qDebug() << "Loading table state:" << dbId << name;
  QString sql = "select state from t_table_columns where database_id=%1 and tablename='%2'";
  QString preparedSql = sql.arg(dbId).arg(name);

  QSqlQuery result = SqlQueryHelper::execSql(preparedSql);
  return result.next() ? result.value(F_STATE).toByteArray() : QByteArray();
}

void DataStore::saveTableState(int dbId, QString name, QByteArray data)
{
  qDebug() << "Saving table state:" << dbId << name;
  QString sql = "insert into t_table_columns(database_id, tablename, state) "
                "values (:db, :tablename, :data) "
                "on conflict (database_id, tablename) do update set state=excluded.state";
  QSqlQuery query = SqlQueryHelper::prepareQuery(sql);
  query.bindValue(":db", dbId);
  query.bindValue(":tablename", name);
  query.bindValue(":data", data);
  SqlQueryHelper::execSql(query);
}

void DataStore::resetTableState(int dbId, QString name)
{
    qDebug() << "Reset table state:" << dbId << name;
    QString sql = "delete from t_table_columns where database_id=:db and tablename=:tablename";
    QSqlQuery query = SqlQueryHelper::prepareQuery(sql);
    query.bindValue(":db", dbId);
    query.bindValue(":tablename", name);
    SqlQueryHelper::execSql(query);
}

bool DataStore::addQueryHistoryItem(int dbId, QString query)
{
  QString sql = "insert into t_query_history(database_id, query) values (:db, :query)";
  QSqlQuery preparedSql = SqlQueryHelper::prepareQuery(sql);
  preparedSql.bindValue(":db", dbId);
  preparedSql.bindValue(":query", query);
  bool resultOk = SqlQueryHelper::execSql(preparedSql);
  return resultOk;
}

bool DataStore::clearQueryHistory(int dbId)
{
  QString sql = "delete from t_query_history where database_id=:db";
  QSqlQuery preparedSql = SqlQueryHelper::prepareQuery(sql);
  preparedSql.bindValue(":db", dbId);
  bool resultOk = SqlQueryHelper::execSql(preparedSql);
  return resultOk;
}
