#include "mysqlplugin.h"
#include "../appconst.h"
#include "mysqldatabase.h"
#include "mysqltable.h"


MysqlPlugin::MysqlPlugin() : DbmsPlugin()
{

}


QString MysqlPlugin::driver()
{
  return DRIVER_MYSQL;
}

DBDatabaseItem *MysqlPlugin::newDatabaseItem(QString caption, QObject *parent)
{
  Q_UNUSED(parent)
  return new MysqlDatabase(caption);
}

DBTableItem *MysqlPlugin::newTableItem(QString caption, QObject *parent)
{
  return new MysqlTableItem(caption, parent);
}

DBViewItem *MysqlPlugin::newViewItem(QString caption, QObject *parent)
{
  Q_UNUSED(caption)
  Q_UNUSED(parent)
  return nullptr;
}

DBProcedureItem *MysqlPlugin::newProcedureItem(QString caption, QObject *parent)
{
  Q_UNUSED(caption)
  Q_UNUSED(parent)
  return nullptr;
}

DBSequenceItem *MysqlPlugin::newSequenceItem(QString caption, QObject *parent)
{
  Q_UNUSED(caption)
  Q_UNUSED(parent)
  return nullptr;
}

DBTriggerItem *MysqlPlugin::newTriggerItem(QString caption, QObject *parent)
{
  Q_UNUSED(caption)
  Q_UNUSED(parent)
  return nullptr;
}

AbstractDatabaseEditForm *MysqlPlugin::formByType(DBObjectItem::ItemType type)
{
  Q_UNUSED(type)
  return nullptr;
}
