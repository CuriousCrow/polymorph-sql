#include "qdbmysqlitem.h"
#include "qdbmysqltableitem.h"
#include "../qfoldertreeitem.h"
#include "../appconst.h"


DBMysqlItem::DBMysqlItem(QString caption)
  : DBDatabaseItem(caption)
{
  setFieldValue(F_DRIVER_NAME, DRIVER_MYSQL);
}

DBMysqlItem::~DBMysqlItem()
{
}

DBTableItem *DBMysqlItem::createNewTableItem(QString caption, QObject *parent)
{
  return new DBMysqlTableItem(caption, parent);
}

bool DBMysqlItem::reloadChildren()
{
  if (!children().isEmpty())
    return false;

  //Creating table items
  FolderTreeItem* tableFolderItem = new FolderTreeItem(tr("Tables"), this);
  tableFolderItem->setChildrenType(Table);
  QStringList tableNames = QSqlDatabase::database(connectionName()).tables();
  foreach (QString name, tableNames){
    createNewTableItem(name, tableFolderItem);
  }

  //Creating views items
  FolderTreeItem* viewFolderItem = new FolderTreeItem(tr("Views"), this);
  viewFolderItem->setChildrenType(View);
  loadViewItems(viewFolderItem);

  //Creating system table items
  FolderTreeItem* systemFolderItem = new FolderTreeItem(tr("System tables"), this);
  systemFolderItem->setChildrenType(Table);
  QStringList sysTableNames = QSqlDatabase::database(connectionName()).tables(QSql::SystemTables);
  foreach (QString name, sysTableNames){
    new DBMysqlTableItem(name, systemFolderItem);
  }

  //  //Creating trigger items
  //  QFolderTreeItem* triggerFolderItem = new QFolderTreeItem(tr("Triggers"), this);
  //  triggerFolderItem->setChildrenType(Trigger);
  //  loadTriggerItems(triggerFolderItem);

  return true;
}

QString DBMysqlItem::getViewListSql()
{
  return "select table_name \"name\" from INFORMATION_SCHEMA.views";
}

QString DBMysqlItem::getSequenceListSql()
{
  return "";
}

QString DBMysqlItem::getTriggerListSql()
{
  return "";
}

QString DBMysqlItem::getProcedureListSql()
{
  return "";
}
