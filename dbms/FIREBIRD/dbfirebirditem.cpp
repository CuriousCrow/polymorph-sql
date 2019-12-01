#include "dbfirebirditem.h"
#include "dbfirebirdtableitem.h"
#include "../appconst.h"

#define SQL_VIEWS "select trim(rdb$relation_name) name, rdb$view_source queryText from rdb$relations where rdb$relation_type=1"

DBFirebirdItem::DBFirebirdItem(QString caption)
  : DBDatabaseItem(caption)
{
  setFieldValue(F_DRIVER_NAME, DRIVER_FIREBIRD);
}

QString DBFirebirdItem::getViewListSql()
{
  return "select trim(rdb$relation_name) name, rdb$view_source queryText from rdb$relations "
         "where rdb$relation_type=1";
}

QString DBFirebirdItem::getSequenceListSql()
{
  return "select rdb$generator_id id, trim(rdb$generator_name) name from rdb$generators where rdb$system_flag = 0";
}

QString DBFirebirdItem::getTriggerListSql()
{
  return "select trim(rdb$trigger_name) name from rdb$triggers where rdb$system_flag = 0";
}

QString DBFirebirdItem::getProcedureListSql()
{
  return "select rdb$procedure_id id, trim(rdb$procedure_name) name from rdb$procedures";
}

DBTableItem *DBFirebirdItem::createNewTableItem(QString caption, QObject *parent)
{
  return new DBFirebirdTableItem(caption, parent);
}


void DBFirebirdItem::loadSequenceItems(DBObjectItem *parentItem)
{
  QString sql = getSequenceListSql();
  QSqlQuery resultSet = QSqlQueryHelper::execSql(sql, connectionName());
  while (resultSet.next()){
    DBSequenceItem* sequenceItem = createNewSequenceItem(resultSet.value(F_NAME).toString(), parentItem);
    sequenceItem->setParentUrl(parentItem->objectUrl());
  }
}
