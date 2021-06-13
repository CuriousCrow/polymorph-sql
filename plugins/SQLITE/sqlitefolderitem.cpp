#include "sqlitefolderitem.h"
#include "sdk/objects/dbtriggeritem.h"
#include "sdk/objects/dbsequenceitem.h"
#include "sdk/objects/appconst.h"
#include "sdk/core/core.h"
#include "sdk/utils/qsqlqueryhelper.h"


SqliteFolderItem::SqliteFolderItem() : FolderTreeItem()
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
    DBSequenceItem* sequenceItem = Core::instance()->dependencyForDriver<DBSequenceItem>(driverName());
    sequenceItem->setFieldValue(F_CAPTION, resultSet.value(F_NAME));
    sequenceItem->setParent(this);
    sequenceItem->setFieldValue(F_CURRENT_VALUE, resultSet.value(F_CURRENT_VALUE).toInt());
    sequenceItem->setParentUrl(objectUrl());
  }
}

void SqliteFolderItem::loadTriggers()
{
  QString sql = "select name name from sqlite_master where type = 'trigger'";
  QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
  while (resultSet.next()) {
    DBTriggerItem* triggerItem = Core::instance()->dependencyForDriver<DBTriggerItem>(driverName());
    triggerItem->setParent(this);
    triggerItem->setFieldValue(F_CAPTION, resultSet.value(F_NAME));
    triggerItem->setFieldValue(F_CURRENT_VALUE, resultSet.value(F_CURRENT_VALUE).toInt());
    triggerItem->setParentUrl(objectUrl());
  }
}

void SqliteFolderItem::loadProcedures()
{

}
