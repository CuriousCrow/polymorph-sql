#include "qdbdatabaseitem.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QUrl>
#include <QIcon>
#include "qdbtableitem.h"
#include "qdbviewitem.h"
#include "qfoldertreeitem.h"
#include "qdbsequenceitem.h"
#include "qdbtriggeritem.h"
#include "qdbprocedureitem.h"


QDBDatabaseItem::QDBDatabaseItem(QString caption, QObject* parent):
  QDBObjectItem(caption, parent)
{
  //1
  registerField("id");
  //2
  registerField("hostName");
  //3
  registerField("userName");
  //4
  registerField("password");
  //5
  registerField("driverName");
  //6
  registerField("databaseName");
}

QDBDatabaseItem::~QDBDatabaseItem()
{
}

bool QDBDatabaseItem::createDbConnection()
{
  QSqlDatabase db = QSqlDatabase::addDatabase(driver(), _connectionName);
  db.setDatabaseName(fieldValue("databaseName").toString());
  db.setUserName(fieldValue("userName").toString());
  db.setPassword(fieldValue("password").toString());

  //Trying to connect
  if (!db.open()){
    QMessageBox::critical(0, "Error", db.lastError().text());
    return false;
  }
  qDebug() << "DB" << fieldValue("caption").toString() << "connected";
  return true;
}

bool QDBDatabaseItem::loadChildren()
{
  if (!children().isEmpty())
    return false;

  //Creating table items
  QFolderTreeItem* tableFolderItem = new QFolderTreeItem(tr("Tables"), this);
  QStringList tableNames = QSqlDatabase::database(connectionName()).tables();
  foreach (QString name, tableNames){
    QDBTableItem* tableItem = new QDBTableItem(name, tableFolderItem);
    tableItem->updateObjectName();
  }

  //Creating views items
  QFolderTreeItem* viewFolderItem = new QFolderTreeItem(tr("Views"), this);
  loadViewItems(viewFolderItem);

  //Creating system table items
  QFolderTreeItem* systemFolderItem = new QFolderTreeItem(tr("System tables"), this);
  QStringList sysTableNames = QSqlDatabase::database(connectionName()).tables(QSql::SystemTables);
  foreach (QString name, sysTableNames){
    QDBTableItem* tableItem = new QDBTableItem(name, systemFolderItem);
    tableItem->updateObjectName();
  }

  //Creating sequence items
  QFolderTreeItem* sequenceFolderItem = new QFolderTreeItem(tr("Sequences"), this);
  loadSequenceItems(sequenceFolderItem);

  //Creating trigger items
  QFolderTreeItem* triggerFolderItem = new QFolderTreeItem(tr("Triggers"), this);
  loadTriggerItems(triggerFolderItem);

  //Creating procedure items
  QFolderTreeItem* procedureFolderItem = new QFolderTreeItem(tr("Procedures"), this);
  loadProcedureItems(procedureFolderItem);

  return true;
}


QUrl QDBDatabaseItem::objectUrl()
{
  QUrl url = QDBObjectItem::objectUrl();
  url.setScheme(driver());
  url.setHost(fieldValue("caption").toString().replace(' ', '_'), QUrl::TolerantMode);
  return url;
}

bool QDBDatabaseItem::insertMe()
{
  QString sql = "insert into t_database (NAME, DRIVER, LOCAL_PATH, HOST_ADDRESS, USERNAME, PASSWORD) "
                "values ('#caption#','#driverName#', '#databaseName#', '#hostName#', '#userName#', '#password#')";
  QSqlQuery sqlResult = QSqlQueryHelper::execSql(fillSqlPattern(sql));
  if (sqlResult.lastError().isValid()){    
    return false;
  }
  else {
    setFieldValue("id", sqlResult.lastInsertId());
    return true;
  }
}

bool QDBDatabaseItem::updateMe()
{
  QString sql = "update t_database set NAME='#caption#', DRIVER='#driverName#',"
    "LOCAL_PATH='#databaseName#',HOST_ADDRESS='#hostName#',"
    "USERNAME='#userName#',PASSWORD='#password#' where id=#id#";

  return !QSqlQueryHelper::execSql(fillSqlPattern(sql)).lastError().isValid();
}

bool QDBDatabaseItem::deleteMe()
{
  QString sql = "delete from t_database where id=#id#";
  return !QSqlQueryHelper::execSql(fillSqlPattern(sql)).lastError().isValid();
}

QVariant QDBDatabaseItem::colData(int column, int role)
{
  switch (role) {
  case Qt::DecorationRole:
    if (column == 0)
      return QIcon(":/icons/database.png");  
  }
  return QDBObjectItem::colData(column, role);
}

int QDBDatabaseItem::type()
{
  return Database;
}

//QString QDBDatabaseItem::fillSqlPattern(QString pattern)
//{
//  foreach(QDBObjectField field, fields) {
//    this->setProperty(qPrintable(field.name), field.value());
//  }
//  return QSqlQueryHelper::fillSqlPattern(pattern, this);
//}

void QDBDatabaseItem::loadViewItems(QDBObjectItem *parentItem)
{
  QString sql = getViewListSql();

  if (sql.isEmpty()){
    QStringList viewNames = QSqlDatabase::database(connectionName()).tables(QSql::Views);
    foreach (QString name, viewNames){
      QDBViewItem* viewItem = new QDBViewItem(name, parentItem);
      viewItem->updateObjectName();
    }
  }
  else {
    QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
    while (resultSet.next()){
      QDBViewItem* viewItem
          = new QDBViewItem(resultSet.value("name").toString(), parentItem);
      viewItem->setQueryText(resultSet.value("queryText").toString());
      viewItem->updateObjectName();
    }
  }
}

void QDBDatabaseItem::loadSequenceItems(QDBObjectItem *parentItem)
{
  QString sql;

  if (isDriver(DRIVER_FIREBIRD)){
    sql = getSequenceListSql();
    QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
    while (resultSet.next()){
      QDBSequenceItem* sequenceItem
          = new QDBSequenceItem(resultSet.value("name").toString(), parentItem);
      sequenceItem->updateObjectName();
    }
  }
  else if (isDriver(DRIVER_POSTGRES)) {
    sql = "SELECT c.relname \"name\" FROM pg_class c WHERE c.relkind = 'S'";
    QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
    while (resultSet.next()) {
      QDBSequenceItem* sequenceItem
        = new QDBSequenceItem(resultSet.value("name").toString(), parentItem);
      sequenceItem->updateObjectName();
    }
  }
}

void QDBDatabaseItem::loadTriggerItems(QDBObjectItem *parentItem)
{
  QString sql = getTriggerListSql();
  if (!sql.isEmpty()){
    QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
    while (resultSet.next()){
      QDBTriggerItem* sequenceItem
          = new QDBTriggerItem(resultSet.value("name").toString(), parentItem);
      sequenceItem->updateObjectName();
    }
  }
}

void QDBDatabaseItem::loadProcedureItems(QDBObjectItem *parentItem)
{
  QString sql = getProcedureListSql();
  if (sql.isEmpty())
    return;

  QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
  while (resultSet.next()){
      QDBProcedureItem* sequenceItem
          = new QDBProcedureItem(resultSet.value("name").toString(), parentItem);
      sequenceItem->updateObjectName();
    }

}

QString QDBDatabaseItem::getViewListSql()
{
  QString sql;
  if (isDriver(DRIVER_SQLITE)) {
    sql = "select trim(name) name, sql queryText from sqlite_master where type='view'";
  }
  else if (isDriver(DRIVER_POSTGRES)) {
    sql = "select table_name \"name\" from INFORMATION_SCHEMA.views where table_schema = 'public'";
  }
  else if (isDriver(DRIVER_MYSQL)) {
    sql = "select table_name \"name\" from INFORMATION_SCHEMA.views";
  }
  return sql;
}

QString QDBDatabaseItem::getSequenceListSql()
{

}

QString QDBDatabaseItem::getTriggerListSql()
{
  QString sql = "";
  if (isDriver(DRIVER_FIREBIRD))
    sql = "select trim(rdb$trigger_name) name from rdb$triggers where rdb$system_flag = 0";
  else if (isDriver(DRIVER_SQLITE))
    sql = "select name name from sqlite_master where type = 'trigger'";
  else if (isDriver(DRIVER_POSTGRES))
    sql = "SELECT trigger_name \"name\" FROM information_schema.triggers";
  return sql;
}

QString QDBDatabaseItem::getProcedureListSql()
{
  QString sql;
  if (isDriver(DRIVER_FIREBIRD))
    sql = sql = "select rdb$procedure_id id, trim(rdb$procedure_name) name from rdb$procedures";
  return sql;
}

QString QDBDatabaseItem::driver()
{
  return fieldValue("driverName").toString();
}

bool QDBDatabaseItem::isDriver(QString name)
{
  return driver() == name;
}
