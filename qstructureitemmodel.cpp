#include "qstructureitemmodel.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "dbms/FIREBIRD/firebirddatabase.h"
#include "dbms/SQLITE/sqlitedatabase.h"
#include "dbms/MYSQL/mysqldatabase.h"
#include "dbms/POSTGRES/postgresdatabase.h"
#include "dbms/appconst.h"
#include <QDebug>
#include "dbms/appurl.h"
#include "qsqlqueryhelper.h"

QStructureItemModel::QStructureItemModel(QObject *parent):
  LStandardTreeModel(parent)
{
  connect(this, SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)),
          SLOT(onAboutToBeRemoved(QModelIndex,int,int)));
}

QStructureItemModel::~QStructureItemModel()
{
}

void QStructureItemModel::appendItem(DBObjectItem *item, DBObjectItem *parent)
{
  addItem(item, parent);
  if (parent)
    item->setParentUrl(parent->objectUrl());
  else
    item->setParentUrl(AppUrl());
}

void QStructureItemModel::appendItem(DBObjectItem *item, QModelIndex parent)
{
  addItem(item, parent);
  if (parent.isValid()) {
    DBObjectItem* parentItem = qobject_cast<DBObjectItem*>(itemByIndex(parent));
    Q_ASSERT(parentItem);
    item->setParentUrl(parentItem->objectUrl());
  }
}

QModelIndex QStructureItemModel::indexByUrl(const AppUrl &url)
{
  return indexByName(url.toString());
}

DBObjectItem *QStructureItemModel::itemByUrl(const AppUrl &url)
{
  return qobject_cast<DBObjectItem*>(itemByName(url.toString()));
}

bool QStructureItemModel::deleteChildren(QModelIndex parent)
{
  return removeRows(0, rowCount(parent), parent);
}

DBDatabaseItem *QStructureItemModel::dbItemByDriver(QString caption, QString driverName)
{
  DBDatabaseItem* item;
  if (driverName == DRIVER_FIREBIRD) {
    item = new FirebirdDatabase(caption);
  }
  else if (driverName == DRIVER_SQLITE) {
    item = new SqliteDatabase(caption);
  }
  else if (driverName == DRIVER_MYSQL) {
    item = new MysqlDatabase(caption);
  }
  else if (driverName == DRIVER_POSTGRES) {
    item = new PostgresDatabase(caption);
  }
  else {
    item = new DBDatabaseItem(caption);
  }
  return item;
}

void QStructureItemModel::onAboutToBeRemoved(const QModelIndex &parent, int first, int last)
{
  for (int row=first; row<last; row++){
    DBObjectItem* item = qobject_cast<DBObjectItem*>(itemByIndex(index(row, 0, parent)));
    emit itemAboutToBeRemoved(item->objectUrl().toString());
  }
}


Qt::ItemFlags QStructureItemModel::flags(const QModelIndex &index) const
{
  DBObjectItem* item = qobject_cast<DBObjectItem*>(itemByIndex(index));
  if ((item->type() == DBObjectItem::Database)
      && item->children().count() > 0){
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  }
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}
