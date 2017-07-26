#include "qdbsqliteitem.h"
#include "../qfoldertreeitem.h"
#include "../qdbtableitem.h"
#include "qdbsqlitetableitem.h"



QDBSqliteItem::QDBSqliteItem(QString caption, QObject *parent) : QDBDatabaseItem(caption, parent)
{
}


bool QDBSqliteItem::loadChildren()
{
  if (!children().isEmpty())
    return false;

  //Creating table items
  QFolderTreeItem* tableFolderItem = new QFolderTreeItem(tr("Tables"), this);
  tableFolderItem->setChildrenType(Table);
  QStringList tableNames = QSqlDatabase::database(connectionName()).tables();
  foreach (QString name, tableNames){
    QDBTableItem* tableItem = new QDBSqliteTableItem(name, tableFolderItem);
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
    QDBTableItem* tableItem = new QDBSqliteTableItem(name, systemFolderItem);
    tableItem->updateObjectName();
  }

  //Creating sequence items
  QFolderTreeItem* sequenceFolderItem = new QFolderTreeItem(tr("Generators"), this);
  sequenceFolderItem->setChildrenType(Sequence);
  loadSequenceItems(sequenceFolderItem);

  //Creating trigger items
  QFolderTreeItem* triggerFolderItem = new QFolderTreeItem(tr("Triggers"), this);
  triggerFolderItem->setChildrenType(Trigger);
  loadTriggerItems(triggerFolderItem);

  return true;
}