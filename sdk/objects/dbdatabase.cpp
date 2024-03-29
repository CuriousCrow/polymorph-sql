#include "dbdatabase.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QIcon>
#include "appconst.h"
#include "appurl.h"
#include "foldertreeitem.h"
#include "utils/sqlqueryhelper.h"

#define S_NOT_SUPPORTED " (not supported)"

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
  //7
  registerField(F_PORT);
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
  if (!fieldValue(F_PORT).isNull())
      db.setPort(fieldValue(F_PORT).toInt());
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
  QString sql = "insert into t_database (NAME, DRIVER, LOCAL_PATH, HOST_ADDRESS, USERNAME, PASSWORD, PORT) "
                "values ('#caption#','#driverName#', '#databaseName#', '#hostName#', '#userName#', '#password#', #port#)";
  QSqlQuery sqlResult = SqlQueryHelper::execSql(fillSqlPatternWithFields(sql));
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
                "USERNAME='#userName#',PASSWORD='#password#', PORT=#port# where id=#id#";

  return execSql(fillSqlPatternWithFields(sql));
}

ActionResult DBDatabaseItem::deleteMe()
{
  qDebug() << "Connections:" << QSqlDatabase::connectionNames();
  QString sql = "delete from t_database where id=#id#";
  return execSql(fillSqlPatternWithFields(sql));
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
      QSqlQuery query(sql.arg(fieldValue(F_DATABASE_NAME).toString()), con);
      if (!query.exec()) {
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
      QSqlQuery query(sql.arg(fieldValue(F_DATABASE_NAME).toString()), con);
      if (query.lastError().isValid()) {
        res = ActionResult(ERR_QUERY_ERROR, "Cannot drops database: " + query.lastError().databaseText());
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
    if (column != 0)
      return QVariant();
    return inStatus(ST_UNSUPPORTED) ? QIcon(":/icons/database_unsupported.png") : QIcon(":/icons/database.png");
  case Qt::UserRole:
    return fieldValue(F_ID);
  case Qt::DisplayRole:
    if (column != 0)
      return DBObjectItem::colData(column, role);
    return fieldValue(0).toString() + (inStatus(ST_UNSUPPORTED) ? S_NOT_SUPPORTED : "");
  }
  return DBObjectItem::colData(column, role);
}

int DBDatabaseItem::type() const
{
    return Database;
}

QString DBDatabaseItem::driver() const
{
  return fieldValue(F_DRIVER_NAME).toString();
}

ObjectStatus DBDatabaseItem::status() const
{
  if (driver().isEmpty())
    return ObjectStatus(ST_UNSUPPORTED, S_NOT_SUPPORTED);
  else
    return ObjectStatus(ST_DEFAULT, "");
}
