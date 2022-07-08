#include "sqliteplugin.h"
#include "objects/appconst.h"
#include "sqlitedatabase.h"
#include "sqlitetable.h"
#include "sqliteviewitem.h"
#include "sqlitefolderitem.h"
#include "objects/dbsequenceitem.h"


SqlitePlugin::SqlitePlugin(QObject *parent) : IocPlugin(parent)
{

}

QList<DBObjectItem::ItemType> SqlitePlugin::supportedTypes()
{
  QList<DBObjectItem::ItemType> types;
  types.append(DBObjectItem::Table);
  types.append(DBObjectItem::View);
  types.append(DBObjectItem::SystemTable);
  types.append(DBObjectItem::Sequence);
  return types;
}

bool SqlitePlugin::registerPlugin(DependencyContainer *c)
{
    c->registerDependency(new DependencyMeta("sqliteDatabase", CLASSMETA(SqliteDatabase), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_SQLITE)->setParam(F_TYPE, DBObjectItem::Database);
    c->registerDependency(new DependencyMeta("sqliteFolder", CLASSMETA(SqliteFolderItem), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_SQLITE)->setParam(F_TYPE, DBObjectItem::Folder);
    c->registerDependency(new DependencyMeta("sqliteTable", CLASSMETA(SqliteTableItem), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_SQLITE)->setParam(F_TYPE, DBObjectItem::Table);
    c->registerDependency(new DependencyMeta("sqliteView", CLASSMETA(SqliteViewItem), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_SQLITE)->setParam(F_TYPE, DBObjectItem::View);
    return true;
}


QString SqlitePlugin::title()
{
    return "Sqlite database support plugin";
}

QString SqlitePlugin::author()
{
    return "Lev Alekseevskiy";
}

int SqlitePlugin::majorVersion()
{
    return 1;
}

int SqlitePlugin::minorVersion()
{
    return 0;
}

FeatureTypes SqlitePlugin::featureTypes()
{
    return FeatureType::DbmsObjects;
}

bool SqlitePlugin::driverSupported(QString driverName)
{
    return driverName.toUpper() == DRIVER_SQLITE;
}

QString SqlitePlugin::driver()
{
    return DRIVER_SQLITE;
}