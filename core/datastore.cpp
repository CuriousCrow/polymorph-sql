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

UniSqlTableModel *DataStore::historyModel(int dbId)
{
  UniSqlTableModel* mHistory = instance()->_queryHistoryModel;
  mHistory->filter()->clear();
  mHistory->filter()->addEqualFilter("database_id", dbId);
  mHistory->select();
  return mHistory;
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
