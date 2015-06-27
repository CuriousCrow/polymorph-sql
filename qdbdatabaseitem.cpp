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
}

QDBDatabaseItem::~QDBDatabaseItem()
{
}

QString QDBDatabaseItem::hostName() const
{
  return _hostName;
}

void QDBDatabaseItem::setHostName(const QString &hostName)
{
  _hostName = hostName;
}
QString QDBDatabaseItem::userName() const
{
  return _userName;
}

void QDBDatabaseItem::setUserName(const QString &userName)
{
  _userName = userName;
}
QString QDBDatabaseItem::password() const
{
  return _password;
}

void QDBDatabaseItem::setPassword(const QString &password)
{
  _password = password;
}

bool QDBDatabaseItem::createDbConnection()
{
  QSqlDatabase db = QSqlDatabase::addDatabase(_driverName, _connectionName);
  db.setDatabaseName(_databaseName);
  db.setUserName(_userName);
  db.setPassword(_password);

  //Trying to connect
  if (!db.open()){
    QMessageBox::critical(0, "Error", db.lastError().text());
    return false;
  }
  qDebug() << "DB" << caption() << "connected";
  return true;
}
QString QDBDatabaseItem::driverName() const
{
  return _driverName;
}

void QDBDatabaseItem::setDriverName(const QString &driverName)
{
  _driverName = driverName;
}

qlonglong QDBDatabaseItem::getId() const
{
  return id;
}

void QDBDatabaseItem::setId(const qlonglong &value)
{
  id = value;
}


QString QDBDatabaseItem::databaseName() const
{
  return _databaseName;
}

void QDBDatabaseItem::setDatabaseName(const QString &databaseName)
{
  _databaseName = databaseName;
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
  url.setScheme(_driverName);
  url.setHost(caption().replace(' ', '_'), QUrl::TolerantMode);
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
    id = sqlResult.lastInsertId().toLongLong();
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


int QDBDatabaseItem::colCount()
{
  return 6;
}

QVariant QDBDatabaseItem::colData(int column, int role)
{
  switch (role) {
  case Qt::DisplayRole:
  case Qt::EditRole:
    switch (column) {
    case 0:
      return caption();
    case 1:
      return hostName();
    case 2:
      return userName();
    case 3:
      return password();
    case 4:
      return databaseName();
    case 5:
      return driverName();
    default:
      return QVariant();
    }
  case Qt::DecorationRole:
    if (column == 0)
      return QIcon(":/icons/database.png");
  default:
    return QVariant();
  }
}

int QDBDatabaseItem::type()
{
  return Database;
}


bool QDBDatabaseItem::setData(int column, QVariant value, int role)
{
  if (role == Qt::EditRole){
    switch (column) {
    case 0:
      setCaption(value.toString());
      break;
    case 1:
      setHostName(value.toString());
      break;
    case 2:
      setUserName(value.toString());
      break;
    case 3:
      setPassword(value.toString());
      break;
    case 4:
      setDatabaseName(value.toString());
    case 5:
      setDriverName(value.toString());
    default:
      break;
    }
  }
  return true;
}

QString QDBDatabaseItem::fillSqlPattern(QString pattern)
{
  return QSqlQueryHelper::fillSqlPattern(pattern, this);
}

void QDBDatabaseItem::loadViewItems(QDBObjectItem *parentItem)
{
  QString sql = "";
  if (_driverName == "QIBASE"){
    sql = "select trim(rdb$relation_name) name, rdb$view_source queryText from rdb$relations "
          "where rdb$relation_type=1";
  }
  if (_driverName == "QSQLITE") {
    sql = "select trim(name) name, sql queryText from sqlite_master where type='view'";
  }

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

  if (_driverName == "QIBASE"){
    sql = "select rdb$generator_id id, trim(rdb$generator_name) name from rdb$generators where rdb$system_flag = 0";
    QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
    while (resultSet.next()){
      QDBSequenceItem* sequenceItem
          = new QDBSequenceItem(resultSet.value("name").toString(), parentItem);
      sequenceItem->updateObjectName();
    }
  }
}

void QDBDatabaseItem::loadTriggerItems(QDBObjectItem *parentItem)
{
  QString sql = "";
  if (_driverName == "QIBASE")
    sql = "select trim(rdb$trigger_name) name from rdb$triggers where rdb$system_flag = 0";
  else if (_driverName == "QSQLITE")
    sql = "select name name from sqlite_master where type = 'trigger'";

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
  QString sql;

  if (_driverName == "QIBASE"){
    sql = "select rdb$procedure_id id, trim(rdb$procedure_name) name from rdb$procedures";
    QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
    while (resultSet.next()){
      QDBProcedureItem* sequenceItem
          = new QDBProcedureItem(resultSet.value("name").toString(), parentItem);
      sequenceItem->updateObjectName();
    }
  }
}
