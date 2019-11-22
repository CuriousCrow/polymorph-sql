#include "qdbsqliteitem.h"
#include "../qfoldertreeitem.h"
#include "../qdbtableitem.h"
#include "qdbsqlitetableitem.h"



QDBSqliteItem::QDBSqliteItem(QString caption)
  : QDBDatabaseItem(caption)
{
}


bool QDBSqliteItem::loadChildren()
{
  if (!children().isEmpty())
    return false;

  //Creating table items
  QFolderTreeItem* tableFolderItem = new QFolderTreeItem(tr("Tables"), this->objectUrl(), this);
  tableFolderItem->setChildrenType(Table);
  tableFolderItem->updateObjectName();
  QStringList tableNames = QSqlDatabase::database(connectionName()).tables();
  foreach (QString name, tableNames){
    QDBTableItem* tableItem = new QDBSqliteTableItem(name, tableFolderItem->objectUrl(), tableFolderItem);
    tableItem->updateObjectName();
  }

  //Creating views items
  QFolderTreeItem* viewFolderItem = new QFolderTreeItem(tr("Views"), this->objectUrl(), this);
  viewFolderItem->setChildrenType(View);
  viewFolderItem->updateObjectName();
  loadViewItems(viewFolderItem);

  //Creating system table items
  QFolderTreeItem* systemFolderItem = new QFolderTreeItem(tr("System tables"), this->objectUrl(), this);
  systemFolderItem->setChildrenType(Table);
  systemFolderItem->updateObjectName();
  QStringList sysTableNames = QSqlDatabase::database(connectionName()).tables(QSql::SystemTables);
  foreach (QString name, sysTableNames){
    QDBTableItem* tableItem = new QDBSqliteTableItem(name, systemFolderItem->objectUrl(), systemFolderItem);
    tableItem->updateObjectName();
  }

  //Creating sequence items
  QFolderTreeItem* sequenceFolderItem = new QFolderTreeItem(tr("Generators"), this->objectUrl(), this);
  sequenceFolderItem->setChildrenType(Sequence);
  sequenceFolderItem->updateObjectName();
  loadSequenceItems(sequenceFolderItem);

  //Creating trigger items
  QFolderTreeItem* triggerFolderItem = new QFolderTreeItem(tr("Triggers"), this->objectUrl(), this);
  triggerFolderItem->setChildrenType(Trigger);
  triggerFolderItem->updateObjectName();
  loadTriggerItems(triggerFolderItem);

  return true;
}

QDBTableItem *QDBSqliteItem::createNewTableItem(QString caption, QUrl url, QObject *parent)
{
  return new QDBSqliteTableItem(caption, url, parent);
}

QString QDBSqliteItem::getViewListSql()
{
  return "select trim(name) name, sql queryText from sqlite_master where type='view'";
}

QString QDBSqliteItem::getSequenceListSql()
{
  return "";
}

QString QDBSqliteItem::getTriggerListSql()
{
  return "select name name from sqlite_master where type = 'trigger'";
}

QString QDBSqliteItem::getProcedureListSql()
{
  return "";
}
