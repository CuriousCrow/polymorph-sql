#include "sqliteplugin.h"
#include "sdk/objects/appconst.h"
#include "sqlitedatabase.h"
#include "sqlitetable.h"
#include "sqliteviewitem.h"
#include "sqlitefolderitem.h"
#include "sdk/objects/dbsequenceitem.h"


SqlitePlugin::SqlitePlugin(QObject *parent) : IocPlugin(parent)
{
    registerDependency(new DependencyMeta("sqliteDatabase", CLASSMETA(SqliteDatabase), InstanceMode::Prototype));
    registerDependency(new DependencyMeta("sqliteFolder", CLASSMETA(SqliteFolderItem), InstanceMode::Prototype));
    registerDependency(new DependencyMeta("sqliteTable", CLASSMETA(SqliteTableItem), InstanceMode::Prototype));
    registerDependency(new DependencyMeta("sqliteView", CLASSMETA(SqliteViewItem), InstanceMode::Prototype));

    registerDependency(new DependencyMeta("baseSequence", CLASSMETA(DBSequenceItem), InstanceMode::Prototype));
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
