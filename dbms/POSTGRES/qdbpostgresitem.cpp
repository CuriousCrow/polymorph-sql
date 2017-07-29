#include "qdbpostgresitem.h"
#include "qdbpostgrestableitem.h"


QDBPostgresItem::QDBPostgresItem(QString caption, QObject *parent) : QDBDatabaseItem(caption, parent)
{

}

QDBPostgresItem::~QDBPostgresItem()
{
}

QString QDBPostgresItem::getViewListSql()
{
  return "select table_name \"name\" from INFORMATION_SCHEMA.views where table_schema = 'public'";
}

QString QDBPostgresItem::getSequenceListSql()
{
  return "";
}

QString QDBPostgresItem::getTriggerListSql()
{
  return "SELECT trigger_name \"name\" FROM information_schema.triggers";
}

QString QDBPostgresItem::getProcedureListSql()
{
  return "";
}

QDBTableItem *QDBPostgresItem::createNewTableItem(QString caption, QObject *parent)
{
  return new QDBPostgresTableItem(caption, parent);
}
