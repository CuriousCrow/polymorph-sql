#include "qdbmysqlitem.h"
#include "qdbmysqltableitem.h"
#include "../qfoldertreeitem.h"


QDBMysqlItem::QDBMysqlItem(QString caption, QObject *parent) : QDBDatabaseItem(caption, parent)
{

}

QDBMysqlItem::~QDBMysqlItem()
{
}

QDBTableItem *QDBMysqlItem::createNewTableItem(QString caption, QObject *parent)
{
  return new QDBMysqlTableItem(caption, parent);
}

bool QDBMysqlItem::loadChildren()
{
  if (!children().isEmpty())
    return false;

  //Creating table items
  QFolderTreeItem* tableFolderItem = new QFolderTreeItem(tr("Tables"), this);
  tableFolderItem->setChildrenType(Table);
  QStringList tableNames = QSqlDatabase::database(connectionName()).tables();
  foreach (QString name, tableNames){
    QDBTableItem* tableItem = new QDBMysqlTableItem(name, tableFolderItem);
    tableItem->updateObjectName();
  }

  //Creating views items
  QFolderTreeItem* viewFolderItem = new QFolderTreeItem(tr("Views"), this);
  viewFolderItem->setChildrenType(View);
  loadViewItems(viewFolderItem);

  //Creating system table items
  QFolderTreeItem* systemFolderItem = new QFolderTreeItem(tr("System tables"), this);
  systemFolderItem->setChildrenType(Table);
  QStringList sysTableNames = QSqlDatabase::database(connectionName()).tables(QSql::SystemTables);
  foreach (QString name, sysTableNames){
    QDBTableItem* tableItem = new QDBMysqlTableItem(name, systemFolderItem);
    tableItem->updateObjectName();
  }

//  //Creating trigger items
//  QFolderTreeItem* triggerFolderItem = new QFolderTreeItem(tr("Triggers"), this);
//  triggerFolderItem->setChildrenType(Trigger);
//  loadTriggerItems(triggerFolderItem);

  return true;
}

QString QDBMysqlItem::getViewListSql()
{
  return "select table_name \"name\" from INFORMATION_SCHEMA.views";
}

QString QDBMysqlItem::getSequenceListSql()
{
  return "";
}

QString QDBMysqlItem::getTriggerListSql()
{
  return "";
}

QString QDBMysqlItem::getProcedureListSql()
{
  return "";
}
