#include "sqliteplugin.h"

#include "sqliteconst.h"
#include "objects/appconst.h"
#include "objects/sqlitedatabase.h"
#include "objects/sqlitetable.h"
#include "objects/sqliteview.h"
#include "objects/sqlitefolderitem.h"
#include "objects/dbsequence.h"


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
    c->registerDependency(new DependencyMeta(B_SQLITE_DATABASE, CLASSMETA(SqliteDatabase), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_SQLITE)->setParam(F_TYPE, DBObjectItem::Database);
    c->registerDependency(new DependencyMeta(B_SQLITE_FOLDER, CLASSMETA(SqliteFolderItem), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_SQLITE)->setParam(F_TYPE, DBObjectItem::Folder);
    c->registerDependency(new DependencyMeta(B_SQLITE_TABLE, CLASSMETA(SqliteTableItem), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_SQLITE)->setParam(F_TYPE, DBObjectItem::Table);
    c->registerDependency(new DependencyMeta(B_SQLITE_VIEW, CLASSMETA(SqliteViewItem), InstanceMode::Prototype))
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
