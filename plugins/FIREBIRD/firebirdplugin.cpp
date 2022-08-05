#include "firebirdplugin.h"
#include "objects/appconst.h"
#include "firebirdfolderitem.h"
#include "firebirddatabase.h"
#include "firebirdtable.h"
#include "firebirdsequence.h"


FirebirdPlugin::FirebirdPlugin(QObject *parent) : IocPlugin(parent)
{

}

QList<DBObjectItem::ItemType> FirebirdPlugin::supportedTypes()
{
  QList<DBObjectItem::ItemType> types;
  types.append(DBObjectItem::Table);
  types.append(DBObjectItem::SystemTable);
  types.append(DBObjectItem::View);
  types.append(DBObjectItem::Sequence);
  types.append(DBObjectItem::Procedure);
  types.append(DBObjectItem::Trigger);
  return types;
}

bool FirebirdPlugin::registerPlugin(DependencyContainer *c)
{
  c->registerDependency(new DependencyMeta("firebirdDatabase", CLASSMETA(FirebirdDatabase), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::Database);
  c->registerDependency(new DependencyMeta("firebirdFolderItem", CLASSMETA(FirebirdFolderItem), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::Folder);
  c->registerDependency(new DependencyMeta("firebirdTableItem", CLASSMETA(FirebirdTable), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::Table);
  c->registerDependency(new DependencyMeta("firebirdSequenceItem", CLASSMETA(FirebirdSequence), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::Sequence);

  return true;
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
