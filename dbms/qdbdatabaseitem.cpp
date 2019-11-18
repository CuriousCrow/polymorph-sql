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
#include "dbms/appconst.h"


QDBDatabaseItem::QDBDatabaseItem(QString caption, QObject* parent):
  QDBObjectItem(caption, parent)
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

QDBDatabaseItem::~QDBDatabaseItem()
{
}

bool QDBDatabaseItem::createDbConnection()
{
  QSqlDatabase db = QSqlDatabase::addDatabase(driver(), _connectionName);
  db.setDatabaseName(fieldValue(F_DATABASE_NAME).toString());
  db.setUserName(fieldValue(F_USERNAME).toString());
  db.setPassword(fieldValue(F_PASSWORD).toString());

  //Trying to connect
  if (!db.open()){
    QMessageBox::critical(nullptr, TITLE_ERROR, db.lastError().text());
    return false;
  }
  qDebug() << "DB" << fieldValue(F_CAPTION).toString() << "connected";
  return true;
}

bool QDBDatabaseItem::loadChildren()
{
  if (!children().isEmpty())
    return false;

  //Creating table items
  QFolderTreeItem* tableFolderItem = new QFolderTreeItem(tr("Tables"), this);
  tableFolderItem->setChildrenType(Table);
  QStringList tableNames = QSqlDatabase::database(connectionName()).tables();
  foreach (QString name, tableNames){
    QDBTableItem* tableItem = createNewTableItem(name, tableFolderItem);
    tableItem->updateObjectName();
  }

  //Creating views items
  QFolderTreeItem* viewFolderItem = new QFolderTreeItem(tr("Views"), this);
  viewFolderItem->setChildrenType(View);
  loadViewItems(viewFolderItem);

  //  //Creating system table items
  QFolderTreeItem* systemFolderItem = new QFolderTreeItem(tr("System tables"), this);
  systemFolderItem->setChildrenType(Table);
  QStringList sysTableNames = QSqlDatabase::database(connectionName()).tables(QSql::SystemTables);
  foreach (QString name, sysTableNames){
    QDBTableItem* tableItem = createNewTableItem(name, systemFolderItem);
    tableItem->updateObjectName();
  }

  //Creating sequence items
  QFolderTreeItem* sequenceFolderItem = new QFolderTreeItem(tr("Sequences"), this);
  sequenceFolderItem->setChildrenType(Sequence);
  loadSequenceItems(sequenceFolderItem);

  //Creating trigger items
  QFolderTreeItem* triggerFolderItem = new QFolderTreeItem(tr("Triggers"), this);
  triggerFolderItem->setChildrenType(Trigger);
  loadTriggerItems(triggerFolderItem);

  //Creating procedure items
  QFolderTreeItem* procedureFolderItem = new QFolderTreeItem(tr("Procedures"), this);
  procedureFolderItem->setChildrenType(Procedure);
  loadProcedureItems(procedureFolderItem);

  return true;
}


QUrl QDBDatabaseItem::objectUrl()
{
  QUrl url = QDBObjectItem::objectUrl();
  url.setScheme(driver());
  url.setHost(fieldValue(F_CAPTION).toString().replace(' ', '_'), QUrl::TolerantMode);
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

void QDBDatabaseItem::loadViewItems(QDBObjectItem *parentItem)
{
  QString sql = getViewListSql();

  if (sql.isEmpty()){
    QStringList viewNames = QSqlDatabase::database(connectionName()).tables(QSql::Views);
    foreach (QString name, viewNames){
      QDBViewItem* viewItem = createNewViewItem(name, parentItem);
      viewItem->updateObjectName();
    }
  }
  else {
    QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
    while (resultSet.next()){
      QDBViewItem* viewItem
          = createNewViewItem(resultSet.value(F_NAME).toString(), parentItem);
      viewItem->setFieldValue(F_QUERY_TEXT, resultSet.value(F_QUERY_TEXT).toString());
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
          = createNewSequenceItem(resultSet.value(F_NAME).toString(), parentItem);
      sequenceItem->updateObjectName();
    }
  }
  else if (isDriver(DRIVER_POSTGRES)) {
//перенесено в СУБД-зависимого наследника
  }
  else if (isDriver(DRIVER_SQLITE)) {
    sql = "SELECT name, seq currentValue FROM sqlite_sequence";
    QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
    while (resultSet.next()) {
      QDBSequenceItem* sequenceItem
          = createNewSequenceItem(resultSet.value(F_NAME).toString(), parentItem);
      sequenceItem->setFieldValue(F_CURRENT_VALUE, resultSet.value(F_CURRENT_VALUE).toInt());
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
          = createNewTriggerItem(resultSet.value(F_NAME).toString(), parentItem);
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
        = createNewProcedureItem(resultSet.value(F_NAME).toString(), parentItem);
    sequenceItem->updateObjectName();
  }

}

QDBTableItem *QDBDatabaseItem::createNewTableItem(QString caption, QObject* parent)
{
  return new QDBTableItem(caption, parent);
}

QDBViewItem *QDBDatabaseItem::createNewViewItem(QString caption, QObject* parent)
{
  return new QDBViewItem(caption, parent);
}

QDBProcedureItem *QDBDatabaseItem::createNewProcedureItem(QString caption, QObject* parent)
{
  return new QDBProcedureItem(caption, parent);
}

QDBSequenceItem *QDBDatabaseItem::createNewSequenceItem(QString caption, QObject* parent)
{
  return new QDBSequenceItem(caption, parent);
}

QDBTriggerItem *QDBDatabaseItem::createNewTriggerItem(QString caption, QObject* parent)
{
  return new QDBTriggerItem(caption, parent);
}

QString QDBDatabaseItem::getViewListSql()
{
  return "";
}

QString QDBDatabaseItem::getSequenceListSql()
{
  return "";
}

QString QDBDatabaseItem::getTriggerListSql()
{
  return "";
}

QString QDBDatabaseItem::getProcedureListSql()
{
  return "";
}

QString QDBDatabaseItem::driver()
{
  return fieldValue(F_DRIVER_NAME).toString();
}

bool QDBDatabaseItem::isDriver(QString name)
{
  return driver() == name;
}
