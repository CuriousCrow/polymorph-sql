#include "mysqlplugin.h"
#include "sdk/objects/appconst.h"
#include "mysqldatabase.h"
#include "mysqltable.h"
#include "mysqlfolderitem.h"
#include "sdk/objects/dbsequenceitem.h"
#include "sdk/objects/dbviewitem.h"
#include "sdk/objects/dbprocedureitem.h"
#include "sdk/objects/dbtriggeritem.h"


MysqlPlugin::MysqlPlugin(QObject *parent) : IocPlugin(parent)
{
  registerDependency(new DependencyMeta("mysqlDatabaseItem", CLASSMETA(MysqlDatabase), InstanceMode::Prototype));
  registerDependency(new DependencyMeta("mysqlFolderItem", CLASSMETA(MysqlFolderItem), InstanceMode::Prototype));
  registerDependency(new DependencyMeta("mysqlTableItem", CLASSMETA(MysqlTableItem), InstanceMode::Prototype));
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
