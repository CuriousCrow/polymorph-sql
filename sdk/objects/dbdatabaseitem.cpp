#include "dbdatabaseitem.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include "appurl.h"
#include <QIcon>
#include "dbtableitem.h"
#include "dbviewitem.h"
#include "foldertreeitem.h"
#include "dbsequenceitem.h"
#include "dbtriggeritem.h"
#include "dbprocedureitem.h"
#include "appconst.h"


DBDatabaseItem::DBDatabaseItem(QString caption):
  DBObjectItem(caption)
{
  //1
  registerField(F_ID);
  //2
  registerField(F_HOSTNAME);
  //3
  registerField(F_USERNAME);
  //4
  registerField(F_PASSWORD);
  //5
  registerField(F_DRIVER_NAME);
  //6
  registerField(F_DATABASE_NAME);
}

DBDatabaseItem::~DBDatabaseItem()
{
}

bool DBDatabaseItem::createDbConnection()
{
  QSqlDatabase db = QSqlDatabase::addDatabase(driver(), _connectionName);
  db.setDatabaseName(fieldValue(F_DATABASE_NAME).toString());
  db.setHostName(fieldValue(F_HOSTNAME).toString());
  db.setUserName(fieldValue(F_USERNAME).toString());
  db.setPassword(fieldValue(F_PASSWORD).toString());
  qDebug() << "Trying to connect:" << info();

  //Trying to connect
  if (!db.open()){
    QMessageBox::critical(nullptr, TITLE_ERROR, db.lastError().text());
    return false;
  }
  qDebug() << "DB" << caption() << "connected";
  return true;
}

QString DBDatabaseItem::info()
{
    return fieldValue(F_HOSTNAME).toString().append(":").append(fieldValue(F_DATABASE_NAME).toString());
}

DBObjectItem *DBDatabaseItem::folderByType(DBObjectItem::ItemType type)
{
  foreach (QObject* child, children()) {
    DBObjectItem* childItem = static_cast<DBObjectItem*>(child);
    if (childItem->type() == DBObjectItem::Folder) {
      if (static_cast<FolderTreeItem*>(childItem)->childrenType() == type)
        return childItem;
    }
  }
  return nullptr;
}

QString DBDatabaseItem::getViewListSql() const
{
    return "";
}

QString DBDatabaseItem::getSequenceListSql() const
{
    return "";
}

QString DBDatabaseItem::getTriggerListSql() const
{
    return "";
}

QString DBDatabaseItem::getProcedureListSql() const
{
    return "";
}

bool DBDatabaseItem::reloadChildren()
{
  if (!children().isEmpty())
    return false;
  return true;
}


AppUrl DBDatabaseItem::objectUrl()
{
  AppUrl url;
  url.setDriver(driver());
  url.setDatabase(caption().replace(' ', '_'));
  return url;
}

ActionResult DBDatabaseItem::insertMe()
{
  QString sql = "insert into t_database (NAME, DRIVER, LOCAL_PATH, HOST_ADDRESS, USERNAME, PASSWORD) "
                "values ('#caption#','#driverName#', '#databaseName#', '#hostName#', '#userName#', '#password#')";
  QSqlQuery sqlResult = QSqlQueryHelper::execSql(fillSqlPattern(sql));
  if (sqlResult.lastError().isValid()){
    return ActionResult(ERR_QUERY_ERROR, sqlResult.lastError().databaseText());
  }
  else {
    setFieldValue("id", sqlResult.lastInsertId());
    return ActionResult(RES_OK_CODE);
  }
}

ActionResult DBDatabaseItem::updateMe()
{
  QString sql = "update t_database set NAME='#caption#', DRIVER='#driverName#',"
                "LOCAL_PATH='#databaseName#',HOST_ADDRESS='#hostName#',"
                "USERNAME='#userName#',PASSWORD='#password#' where id=#id#";

  return execSql(fillSqlPattern(sql));
}

ActionResult DBDatabaseItem::deleteMe()
{
  qDebug() << "Connections:" << QSqlDatabase::connectionNames();
  QString sql = "delete from t_database where id=#id#";
  return execSql(fillSqlPattern(sql));
}

ActionResult DBDatabaseItem::createDatabase()
{
  ActionResult res;
  qDebug() << "Create database:" << fieldValue(F_DATABASE_NAME).toString();
  QString conName = "Create_" + fieldValue(F_DATABASE_NAME).toString();
  {
    QSqlDatabase con = QSqlDatabase::addDatabase(fieldValue(F_DRIVER_NAME).toString(), conName);
    con.setHostName(fieldValue(F_HOSTNAME).toString());
    con.setUserName(fieldValue(F_USERNAME).toString());
    con.setPassword(fieldValue(F_PASSWORD).toString());

    if (con.open()) {
      QString sql = "CREATE DATABASE \"%1\"";
      QSqlQuery query = con.exec(sql.arg(fieldValue(F_DATABASE_NAME).toString()));

      if (query.lastError().isValid()) {
        res = ActionResult(ERR_QUERY_ERROR, "Cannot create database " + query.lastError().databaseText());
      }
    }
    else {
      res = ActionResult(ERR_QUERY_ERROR, "Cannot connect DBMS server: " + con.lastError().databaseText());
    }
  }
  QSqlDatabase::removeDatabase(conName);
  return res;
}

ActionResult DBDatabaseItem::dropDatabase()
{
  ActionResult res;
  qDebug() << "Drop database:" << fieldValue(F_DATABASE_NAME).toString();
  QString conName = "Drop_" + fieldValue(F_DATABASE_NAME).toString();
  {
    QSqlDatabase con = QSqlDatabase::addDatabase(fieldValue(F_DRIVER_NAME).toString(), conName);
    con.setHostName(fieldValue(F_HOSTNAME).toString());
    con.setUserName(fieldValue(F_USERNAME).toString());
    con.setPassword(fieldValue(F_PASSWORD).toString());

    if (con.open()) {
      QString sql = "DROP DATABASE \"%1\"";
      QSqlQuery query = con.exec(sql.arg(fieldValue(F_DATABASE_NAME).toString()));
      if (query.lastError().isValid()) {
        res = ActionResult(ERR_QUERY_ERROR, "Cannot create database: " + query.lastError().databaseText());
      }
    }
    else {
      res = ActionResult(ERR_QUERY_ERROR, "Cannot connect DBMS server: " + con.lastError().databaseText());
    }
  }
  QSqlDatabase::removeDatabase(conName);
  return res;
}

QString DBDatabaseItem::getAllObjectListSql() const
{
    return "";
}

QVariant DBDatabaseItem::colData(int column, int role) const
{
  switch (role) {
  case Qt::DecorationRole:
    return (column == 0) ? QIcon(":/icons/database.png") : QVariant();
  case Qt::UserRole:
    return fieldValue(F_ID);
  }
  return DBObjectItem::colData(column, role);
}

int DBDatabaseItem::type() const
{
    return Database;
}

void DBDatabaseItem::onFolderRequestReload()
{

}

QString DBDatabaseItem::driver()
{
  return fieldValue(F_DRIVER_NAME).toString();
}

bool DBDatabaseItem::isDriver(QString name)
{
  return driver() == name;
}
