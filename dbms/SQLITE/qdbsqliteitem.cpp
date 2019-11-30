#include "qdbsqliteitem.h"
#include "../qfoldertreeitem.h"
#include "../qdbtableitem.h"
#include "../appconst.h"
#include "qdbsqlitetableitem.h"



QDBSqliteItem::QDBSqliteItem(QString caption)
  : QDBDatabaseItem(caption)
{
  setFieldValue(F_DRIVER_NAME, DRIVER_SQLITE);
}


bool QDBSqliteItem::reloadChildren()
{
  if (!children().isEmpty())
    return false;

  //Creating table items
  QFolderTreeItem* tableFolderItem = new QFolderTreeItem(tr("Tables"), this);
  tableFolderItem->setChildrenType(Table);
  QStringList tableNames = QSqlDatabase::database(connectionName()).tables();
  foreach (QString name, tableNames){
    new QDBSqliteTableItem(name, tableFolderItem);
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
    new QDBSqliteTableItem(name, systemFolderItem);
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

QDBTableItem *QDBSqliteItem::createNewTableItem(QString caption, QObject *parent)
{
  return new QDBSqliteTableItem(caption, parent);
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

void QDBSqliteItem::loadSequenceItems(QDBObjectItem *parentItem)
{
  QString sql = "SELECT name, seq currentValue FROM sqlite_sequence";
  QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
  while (resultSet.next()) {
    QDBSequenceItem* sequenceItem
        = createNewSequenceItem(resultSet.value(F_NAME).toString(), parentItem);
    sequenceItem->setFieldValue(F_CURRENT_VALUE, resultSet.value(F_CURRENT_VALUE).toInt());
    sequenceItem->setParentUrl(parentItem->objectUrl());
  }
}
