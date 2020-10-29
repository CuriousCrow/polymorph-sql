#include "datastore.h"
#include "appsettings.h"
#include <QMessageBox>
#include <QDebug>
#include <QApplication>
#include <QSqlRecord>
#include "../dbms/appconst.h"
#include "../qsqlqueryhelper.h"
#include "core.h"


DataStore* DataStore::_singleton = nullptr;

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

  _structureModel = new QStructureItemModel(this);
  initRegisteredDatabases();

  //Query history model (one for all databases)
  _queryHistoryModel = new UniSqlTableModel(this);
  _queryHistoryModel->setTable("t_query_history");
  _queryHistoryModel->orderBy(F_ID, Qt::DescendingOrder);
}

void DataStore::initRegisteredDatabases()
{
  QString sql = "select id id, name caption, driver driverName, local_path databaseName, "
                "host_address hostName, username userName, password password from t_database";
  QSqlQuery sqlResult = QSqlQueryHelper::execSql(sql);
  while (sqlResult.next()) {
    QSqlRecord rec = sqlResult.record();
    QString caption = rec.value(F_CAPTION).toString();
    QString driverName = rec.value(F_DRIVER_NAME).toString();
    DbmsPlugin* plugin = Core::module(driverName);
    if (!plugin) {
      qWarning() << "Can't load dbms plugin:" << driverName;
      continue;
    }
    DBDatabaseItem* item = plugin->newDatabaseItem(caption);
    for (int i=0; i<rec.count(); i++) {
      item->setFieldValue(rec.fieldName(i), rec.value(i));
    }
    _structureModel->appendItem(item);
  }
  return;
}

DataStore *DataStore::instance(QObject* parent)
{
  if (!_singleton)
    _singleton = new DataStore(parent);
  return _singleton;
}

QStructureItemModel *DataStore::structureModel()
{
  return instance()->_structureModel;
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

int DataStore::databaseIdFromItem(DBObjectItem *item)
{
  DBObjectItem* curItem = item;
  while(curItem && curItem->type() != DBObjectItem::Database) {
      curItem = qobject_cast<DBObjectItem*>(curItem->parent());
  }
  return curItem->fieldValue(F_ID).toInt();
}

UniSqlTableModel *DataStore::historyModel(int dbId)
{
  UniSqlTableModel* mHistory = instance()->_queryHistoryModel;
  mHistory->filter()->clear();
  mHistory->filter()->addEqualFilter(F_DATABASE_ID, dbId);
  mHistory->select();
  return mHistory;
}

QByteArray DataStore::loadTableState(int dbId, QString name)
{
  qDebug() << "Loading table state:" << dbId << name;
  QString sql = "select state from t_table_columns where database_id=%1 and tablename='%2'";
  QString preparedSql = sql.arg(dbId).arg(name);

  QSqlQuery result = QSqlQueryHelper::execSql(preparedSql);
  return result.next() ? result.value(F_STATE).toByteArray() : QByteArray();
}

void DataStore::saveTableState(int dbId, QString name, QByteArray data)
{
  qDebug() << "Saving table state:" << dbId << name;
  QString sql = "insert into t_table_columns(database_id, tablename, state) "
                "values (:db, :tablename, :data) "
                "on conflict (database_id, tablename) do update set state=excluded.state";
  QSqlQuery query = QSqlQueryHelper::prepareQuery(sql);
  query.bindValue(":db", dbId);
  query.bindValue(":tablename", name);
  query.bindValue(":data", data);
  QSqlQueryHelper::execSql(query);
}

bool DataStore::addQueryHistoryItem(int dbId, QString query)
{
  QString sql = "insert into t_query_history(database_id, query) values (:db, :query)";
  QSqlQuery preparedSql = QSqlQueryHelper::prepareQuery(sql);
  preparedSql.bindValue(":db", dbId);
  preparedSql.bindValue(":query", query);
  bool resultOk = QSqlQueryHelper::execSql(preparedSql);
  return resultOk;
}
