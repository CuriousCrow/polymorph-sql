#include "firebirdplugin.h"
#include "sdk/objects/appconst.h"
#include "firebirdfolderitem.h"
#include "firebirddatabase.h"
#include "firebirdtable.h"


FirebirdPlugin::FirebirdPlugin(QObject *parent) : IocPlugin(parent)
{
    registerDependency(new DependencyMeta("firebirdDatabase", CLASSMETA(FirebirdDatabase), InstanceMode::Prototype));
    registerDependency(new DependencyMeta("firebirdFolderItem", CLASSMETA(FirebirdFolderItem), InstanceMode::Prototype));
    registerDependency(new DependencyMeta("firebirdTableItem", CLASSMETA(FirebirdTable), InstanceMode::Prototype));
}

QList<DBObjectItem::ItemType> FirebirdPlugin::supportedTypes()
{
  QList<DBObjectItem::ItemType> types;
  types.append(DBObjectItem::Table);
  types.append(DBObjectItem::View);
  types.append(DBObjectItem::Sequence);
  types.append(DBObjectItem::Procedure);
  types.append(DBObjectItem::Trigger);
  return types;
}


QString FirebirdPlugin::title()
{
    return "Firebird database support plugin";
}

QString FirebirdPlugin::author()
{
    return "Lev Alekseevskiy";
}

int FirebirdPlugin::majorVersion()
{
    return 1;
}

int FirebirdPlugin::minorVersion()
{
    return 0;
}

FeatureTypes FirebirdPlugin::featureTypes()
{
    return FeatureType::DbmsObjects;
}

bool FirebirdPlugin::driverSupported(QString driverName)
{
    return driverName.toUpper() == DRIVER_FIREBIRD;
}

QString FirebirdPlugin::driver()
{
    return DRIVER_FIREBIRD;
}
