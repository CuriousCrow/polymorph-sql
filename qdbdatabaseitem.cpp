#include "qdbdatabaseitem.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QUrl>
#include <QIcon>
#include "qdbtableitem.h"
#include "qfoldertreeitem.h"

#include <QMetaProperty>

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

  //Folder items for each database object type
  QFolderTreeItem* tableFolderItem = new QFolderTreeItem("Tables", this);
  QFolderTreeItem* sequenceFolderItem = new QFolderTreeItem("Sequences", this);
  QFolderTreeItem* viewFolderItem = new QFolderTreeItem("Views", this);
  QFolderTreeItem* triggerFolderItem = new QFolderTreeItem("Triggers", this);
  QFolderTreeItem* procedureFolderItem = new QFolderTreeItem("Procedures", this);

  //Creating table items
  QStringList tableNames = QSqlDatabase::database(connectionName()).tables();
  foreach (QString name, tableNames){
    QDBTableItem* tableItem = new QDBTableItem(name, tableFolderItem);
    tableItem->updateObjectName();
  }
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
