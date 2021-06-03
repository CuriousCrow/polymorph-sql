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
    DBObjectItem* childItem = qobject_cast<DBObjectItem*>(child);
    if (childItem->type() == DBObjectItem::Folder) {
      if (qobject_cast<FolderTreeItem*>(childItem)->childrenType() == type)
        return childItem;
    }
  }
  return nullptr;
}

bool DBDatabaseItem::reloadChildren()
{
  if (!children().isEmpty())
    return false;

//  //Creating table items
//  FolderTreeItem* tableFolderItem = new FolderTreeItem(FOLDER_TABLES, tr("Tables"), this);
//  tableFolderItem->setParentUrl(this->objectUrl());

//  tableFolderItem->setChildrenType(Table);
//  connect(tableFolderItem, SIGNAL(reloadMe()),
//          this, SLOT(onFolderRequestReload()));
//  loadTableItems(tableFolderItem);

//  //Creating views items
//  FolderTreeItem* viewFolderItem = new FolderTreeItem(FOLDER_VIEWS, tr("Views"), this);
//  viewFolderItem->setChildrenType(View);
//  viewFolderItem->setParentUrl(this->objectUrl());
//  connect(viewFolderItem, SIGNAL(reloadMe()),
//          this, SLOT(onFolderRequestReload()));
//  loadViewItems(viewFolderItem);

//  //  //Creating system table items
//  FolderTreeItem* systemFolderItem = new FolderTreeItem(FOLDER_SYSTABLES, tr("System tables"), this);
//  systemFolderItem->setChildrenType(Table);
//  systemFolderItem->setParentUrl(this->objectUrl());

//  QStringList sysTableNames = QSqlDatabase::database(connectionName()).tables(QSql::SystemTables);
//  foreach (QString name, sysTableNames){
//    DBTableItem* sysTableItem = createNewTableItem(name, systemFolderItem);
//    sysTableItem->setParentUrl(systemFolderItem->objectUrl());
//  }

//  //Creating sequence items
//  FolderTreeItem* sequenceFolderItem = new FolderTreeItem(FOLDER_SEQUENCES, tr("Sequences"), this);
//  sequenceFolderItem->setChildrenType(Sequence);
//  sequenceFolderItem->setParentUrl(this->objectUrl());
//  connect(sequenceFolderItem, SIGNAL(reloadMe()),
//          this, SLOT(onFolderRequestReload()));
//  loadSequenceItems(sequenceFolderItem);

//  //Creating trigger items
//  FolderTreeItem* triggerFolderItem = new FolderTreeItem(FOLDER_TRIGGERS, tr("Triggers"), this);
//  triggerFolderItem->setChildrenType(Trigger);
//  triggerFolderItem->setParentUrl(this->objectUrl());
//  connect(triggerFolderItem, SIGNAL(reloadMe()),
//          this, SLOT(onFolderRequestReload()));
//  loadTriggerItems(triggerFolderItem);

//  //Creating procedure items
//  FolderTreeItem* procedureFolderItem = new FolderTreeItem(FOLDER_PROCEDURES, tr("Procedures"), this);
//  procedureFolderItem->setChildrenType(Procedure);
//  procedureFolderItem->setParentUrl(this->objectUrl());
//  connect(procedureFolderItem, SIGNAL(reloadMe()),
//          this, SLOT(onFolderRequestReload()));
//  loadProcedureItems(procedureFolderItem);

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
  FolderTreeItem* folderItem = qobject_cast<FolderTreeItem*>(sender());
  qDebug() << "Folder" << folderItem->caption() << "reload request";
  switch (folderItem->childrenType()) {
  case DBObjectItem::Table:
    loadTableItems(folderItem);
    break;
  case DBObjectItem::View:
    loadViewItems(folderItem);
    break;
  case DBObjectItem::Sequence:
    loadSequenceItems(folderItem);
    break;
  case DBObjectItem::Trigger:
    loadTriggerItems(folderItem);
    break;
  case DBObjectItem::Procedure:
    loadProcedureItems(folderItem);
    break;
  default:
    break;
  }
}

void DBDatabaseItem::loadTableItems(DBObjectItem *parentItem)
{
  QStringList tableNames = QSqlDatabase::database(connectionName()).tables();
  foreach (QString name, tableNames){
    AppUrl folderUrl = parentItem->objectUrl();
    DBTableItem* tableItem = createNewTableItem(name, parentItem);
    tableItem->setParentUrl(parentItem->objectUrl());
  }
}

void DBDatabaseItem::loadViewItems(DBObjectItem *parentItem)
{
  QString sql = getViewListSql();

  if (sql.isEmpty()){
    QStringList viewNames = QSqlDatabase::database(connectionName()).tables(QSql::Views);
    foreach (QString name, viewNames){
      DBViewItem* viewItem = createNewViewItem(name, parentItem);
      viewItem->setParentUrl(parentItem->objectUrl());
    }
  }
  else {
    QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
    while (resultSet.next()){
      DBViewItem* viewItem
          = createNewViewItem(resultSet.value(F_NAME).toString(), parentItem);
      viewItem->setFieldValue(F_QUERY_TEXT, resultSet.value(F_QUERY_TEXT).toString());
      viewItem->setParentUrl(parentItem->objectUrl());
    }
  }
}

void DBDatabaseItem::loadSequenceItems(DBObjectItem *parentItem)
{
  Q_UNUSED(parentItem)
  //Should be overritten in descendants
}

void DBDatabaseItem::loadTriggerItems(DBObjectItem *parentItem)
{
  QString sql = getTriggerListSql();
  if (!sql.isEmpty()){
    QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
    while (resultSet.next()){
      DBTriggerItem* triggerItem = createNewTriggerItem(resultSet.value(F_NAME).toString(), parentItem);
      triggerItem->setParentUrl(parentItem->objectUrl());
    }
  }
}

void DBDatabaseItem::loadProcedureItems(DBObjectItem *parentItem)
{
  QString sql = getProcedureListSql();
  if (sql.isEmpty())
    return;

  QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());

  while (resultSet.next()){
    DBProcedureItem* procItem = createNewProcedureItem(resultSet.value(F_NAME).toString(), parentItem);
    procItem->setParentUrl(parentItem->objectUrl());
  }

}

DBTableItem *DBDatabaseItem::createNewTableItem(QString caption, QObject* parent)
{
  return new DBTableItem(caption, parent);
}

DBViewItem *DBDatabaseItem::createNewViewItem(QString caption, QObject* parent)
{
  return new DBViewItem(caption, parent);
}

DBProcedureItem *DBDatabaseItem::createNewProcedureItem(QString caption, QObject* parent)
{
  return new DBProcedureItem(caption, parent);
}

DBSequenceItem *DBDatabaseItem::createNewSequenceItem(QString caption, QObject* parent)
{
  return new DBSequenceItem(caption, parent);
}

DBTriggerItem *DBDatabaseItem::createNewTriggerItem(QString caption, QObject* parent)
{
  return new DBTriggerItem(caption, parent);
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

QString DBDatabaseItem::getAllObjectListSql() const
{
  return "";
}

QString DBDatabaseItem::driver()
{
  return fieldValue(F_DRIVER_NAME).toString();
}

bool DBDatabaseItem::isDriver(QString name)
{
  return driver() == name;
}
