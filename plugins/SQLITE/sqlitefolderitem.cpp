#include "sqlitefolderitem.h"
#include "sdk/objects/dbtriggeritem.h"
#include "sdk/objects/dbsequenceitem.h"
#include "sdk/objects/appconst.h"
#include "core/basepluginmanager.h"
#include "qsqlqueryhelper.h"


SqliteFolderItem::SqliteFolderItem(QObject *parent) : FolderTreeItem(parent)
{
}


void SqliteFolderItem::loadChildren()
{
    switch (childrenType()) {
    case DBObjectItem::Sequence:
        loadSequences();
        break;
    case DBObjectItem::Trigger:
        loadTriggers();
        break;
    case DBObjectItem::Procedure:
        loadProcedures();
        break;
    default:
        FolderTreeItem::loadChildren();
    }
}

void SqliteFolderItem::loadSequences()
{
  QString sql = "SELECT name, seq currentValue FROM sqlite_sequence";
  QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
  while (resultSet.next()) {
    DBSequenceItem* sequenceItem = qobject_cast<DBSequenceItem*>(
                BasePluginManager::instance()->newDbmsObject(driverName(),
                                                       DBObjectItem::Sequence,
                                                       resultSet.value(F_NAME).toString(),
                                                       this));
    sequenceItem->setFieldValue(F_CURRENT_VALUE, resultSet.value(F_CURRENT_VALUE).toInt());
    sequenceItem->setParentUrl(objectUrl());
  }
}

void SqliteFolderItem::loadTriggers()
{
  QString sql = "select name name from sqlite_master where type = 'trigger'";
  QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
  while (resultSet.next()) {
      DBTriggerItem* triggerItem = qobject_cast<DBTriggerItem*>(
                  BasePluginManager::instance()->newDbmsObject(driverName(),
                                                         DBObjectItem::Trigger,
                                                         resultSet.value(F_NAME).toString(),
                                                         this));
    triggerItem->setFieldValue(F_CURRENT_VALUE, resultSet.value(F_CURRENT_VALUE).toInt());
    triggerItem->setParentUrl(objectUrl());
  }
}

void SqliteFolderItem::loadProcedures()
{

}
