#include "firebirdfolderitem.h"
#include "utils/sqlqueryhelper.h"
#include "core/core.h"
#include "objects/dbprocedureitem.h"
#include "objects/dbtriggeritem.h"
#include "objects/dbsequenceitem.h"
#include "objects/dbusertype.h"
#include "objects/appconst.h"


FirebirdFolderItem::FirebirdFolderItem() : FolderTreeItem()
{
}


void FirebirdFolderItem::loadChildren()
{
  QString sql;
  switch (childrenType()) {
  case DBObjectItem::Table:
  case DBObjectItem::View:
  case DBObjectItem::SystemTable:
    FolderTreeItem::loadChildren();
    return;
  case DBObjectItem::Sequence:
    sql = "select rdb$generator_id id, trim(rdb$generator_name) name from rdb$generators where rdb$system_flag = 0";
    break;
  case DBObjectItem::Procedure:
    sql = "select rdb$procedure_id id, trim(rdb$procedure_name) name from rdb$procedures";
    break;
  case DBObjectItem::Trigger:
    sql = "select trim(rdb$trigger_name) name from rdb$triggers where rdb$system_flag = 0";
    break;
  case DBObjectItem::UserType:
    sql = "select trim(rdb$field_name) name from rdb$fields where rdb$field_name not like 'RDB$%' order by rdb$field_name";
    break;
  default:
    return;
  }

  QSqlQuery resultSet = SqlQueryHelper::execSql(sql, connectionName());
  while (resultSet.next()){
    DBObjectItem* childItem = nullptr;
    switch (childrenType()) {
    case DBObjectItem::Sequence:
      childItem = _core->dependencyForDriver<DBSequenceItem>(driverName());
      break;
    case DBObjectItem::Procedure:
      childItem = _core->dependencyForDriver<DBProcedureItem>(driverName());
      break;
    case DBObjectItem::Trigger:
      childItem = _core->dependencyForDriver<DBTriggerItem>(driverName());
      break;
    case DBObjectItem::UserType:
      childItem = _core->dependencyForDriver<DBUserType>(driverName());
      break;
    default:
      break;
    }
    if (childItem) {
      childItem->setFieldValue(F_CAPTION, resultSet.value(F_NAME));
      childItem->setParent(this);
      childItem->setParentUrl(objectUrl());
    }
  }
}


QString FirebirdFolderItem::folderName(ItemType type)
{
  if (type == DBObjectItem::UserType)
    return tr("Domains");
  return FolderTreeItem::folderName(type);
}
