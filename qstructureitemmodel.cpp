#include "qstructureitemmodel.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "dbms/FIREBIRD/qdbfirebirditem.h"
#include "dbms/SQLITE/qdbsqliteitem.h"
#include "dbms/MYSQL/qdbmysqlitem.h"
#include "dbms/POSTGRES/qdbpostgresitem.h"
#include "dbms/appconst.h"
#include <QDebug>
#include <QUrl>
#include "qsqlqueryhelper.h"

QStructureItemModel::QStructureItemModel(QObject *parent, QSqlDatabase db):
  LStandardTreeModel(parent)
{
  _db = db;
  loadRegisteredDatabases();
  connect(this, SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)),
          SLOT(onAboutToBeRemoved(QModelIndex,int,int)));
}

QStructureItemModel::~QStructureItemModel()
{
}

void QStructureItemModel::appendItem(QDBObjectItem *item, QDBObjectItem *parent)
{
  addItem(item, parent);
  if (parent)
    item->setParentUrl(parent->objectUrl());
  else
    item->setParentUrl(QUrl());
}

void QStructureItemModel::appendItem(QDBObjectItem *item, QModelIndex parent)
{
  addItem(item, parent);
  if (parent.isValid()) {
    QDBObjectItem* parentItem = qobject_cast<QDBObjectItem*>(itemByIndex(parent));
    Q_ASSERT(parentItem);
    item->setParentUrl(parentItem->objectUrl());
  }
}

bool QStructureItemModel::deleteChildren(QModelIndex parent)
{
  return removeRows(0, rowCount(parent), parent);
}

bool QStructureItemModel::loadRegisteredDatabases()
{
  QString sql = "select id id, name caption, driver driverName, local_path databaseName, "
                "host_address hostName, username userName, password password from t_database";
  QSqlQuery sqlResult = QSqlQueryHelper::execSql(sql);
  while (sqlResult.next()) {
    QSqlRecord rec = sqlResult.record();
    QString caption = rec.value(F_CAPTION).toString();
    QString driverName = rec.value(F_DRIVER_NAME).toString();
    QDBDatabaseItem* item = dbItemByDriver(caption, driverName);
    for (int i=0; i<rec.count(); i++) {
      item->setFieldValue(rec.fieldName(i), rec.value(i));
    }
    appendItem(item);
  }
  return true;
}

QDBDatabaseItem *QStructureItemModel::dbItemByDriver(QString caption, QString driverName)
{
  QDBDatabaseItem* item;
  if (driverName == DRIVER_FIREBIRD) {
    item = new QDBFirebirdItem(caption);
  }
  else if (driverName == DRIVER_SQLITE) {
    item = new QDBSqliteItem(caption);
  }
  else if (driverName == DRIVER_MYSQL) {
    item = new QDBMysqlItem(caption);
  }
  else if (driverName == DRIVER_POSTGRES) {
    item = new QDBPostgresItem(caption);
  }
  else {
    item = new QDBDatabaseItem(caption);
  }
  return item;
}

void QStructureItemModel::onAboutToBeRemoved(const QModelIndex &parent, int first, int last)
{
  for (int row=first; row<last; row++){
    QDBObjectItem* item = qobject_cast<QDBObjectItem*>(itemByIndex(index(row, 0, parent)));
    emit itemAboutToBeRemoved(item->objectUrl().url());
  }
}


Qt::ItemFlags QStructureItemModel::flags(const QModelIndex &index) const
{
  QDBObjectItem* item = qobject_cast<QDBObjectItem*>(itemByIndex(index));
  if ((item->type() == QDBObjectItem::Database)
      && item->children().count() > 0){
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  }
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}
