#include "datastore.h"
#include "appsettings.h"
#include <QMessageBox>
#include <QDebug>
#include <QApplication>
#include "../dbms/appconst.h"


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

  _structureModel = new QStructureItemModel(this, appDB);
}

DataStore *DataStore::instance(QObject* parent)
{
  if (!_singleton)
    _singleton = new DataStore(parent);
  return _singleton;
}

QStructureItemModel *DataStore::structureModel()
{
  return _structureModel;
}
