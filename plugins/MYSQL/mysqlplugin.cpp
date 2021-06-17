#include "mysqlplugin.h"
#include "objects/appconst.h"
#include "mysqldatabase.h"
#include "mysqltable.h"
#include "mysqlfolderitem.h"
#include "objects/dbsequenceitem.h"
#include "objects/dbviewitem.h"
#include "objects/dbprocedureitem.h"
#include "objects/dbtriggeritem.h"


MysqlPlugin::MysqlPlugin(QObject *parent) : IocPlugin(parent)
{

}

QList<DBObjectItem::ItemType> MysqlPlugin::supportedTypes()
{
  QList<DBObjectItem::ItemType> types;
  types.append(DBObjectItem::Table);
  types.append(DBObjectItem::View);
  types.append(DBObjectItem::Sequence);
  types.append(DBObjectItem::Procedure);
  types.append(DBObjectItem::Trigger);
  return types;
}

bool MysqlPlugin::registerPlugin(DependencyContainer *c)
{
  c->registerDependency(new DependencyMeta("mysqlDatabaseItem", CLASSMETA(MysqlDatabase), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::Database);
  c->registerDependency(new DependencyMeta("mysqlFolderItem", CLASSMETA(MysqlFolderItem), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::Folder);
  c->registerDependency(new DependencyMeta("mysqlTableItem", CLASSMETA(MysqlTableItem), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::Table);
  return true;
}

QString MysqlPlugin::title()
{
    return "MySQL database support plugin";
}

QString MysqlPlugin::author()
{
    return "Lev Alekseevskiy";
}

int MysqlPlugin::majorVersion()
{
    return 1;
}

int MysqlPlugin::minorVersion()
{
    return 0;
}

FeatureTypes MysqlPlugin::featureTypes()
{
    return FeatureType::DbmsObjects;
}

bool MysqlPlugin::driverSupported(QString driverName)
{
    return driverName.toUpper() == DRIVER_MYSQL;
}

QString MysqlPlugin::driver()
{
    return DRIVER_MYSQL;
}
