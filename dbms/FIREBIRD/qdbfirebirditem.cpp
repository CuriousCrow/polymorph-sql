#include "qdbfirebirditem.h"
#include "qdbfirebirdtableitem.h"

#define SQL_VIEWS "select trim(rdb$relation_name) name, rdb$view_source queryText from rdb$relations where rdb$relation_type=1"

QDBFirebirdItem::QDBFirebirdItem(QString caption, QObject *parent)
  : QDBDatabaseItem(caption, parent)
{
}

QString QDBFirebirdItem::getViewListSql()
{
  return "select trim(rdb$relation_name) name, rdb$view_source queryText from rdb$relations "
         "where rdb$relation_type=1";
}

QString QDBFirebirdItem::getSequenceListSql()
{
  return "select rdb$generator_id id, trim(rdb$generator_name) name from rdb$generators where rdb$system_flag = 0";
}

QString QDBFirebirdItem::getTriggerListSql()
{
  return "select trim(rdb$trigger_name) name from rdb$triggers where rdb$system_flag = 0";
}

QString QDBFirebirdItem::getProcedureListSql()
{
  return "select rdb$procedure_id id, trim(rdb$procedure_name) name from rdb$procedures";
}

QDBTableItem *QDBFirebirdItem::createNewTableItem(QString caption, QObject *parent)
{
  return new QDBFirebirdTableItem(caption, parent);
}
