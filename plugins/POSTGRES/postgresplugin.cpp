#include "postgresplugin.h"
#include "sdk/objects/appconst.h"
#include "postgresdatabase.h"
#include "postgrestable.h"
#include "postgressequence.h"
#include "postgrestriggeritem.h"
#include "postgresfunctionitem.h"
#include "postgresviewitem.h"
#include "postgresfolderitem.h"
#include "postgresprimarykey.h"
#include "postgrescheckconstraint.h"
#include "postgresforeignkey.h"
#include "postgresuniqueconstraint.h"
#include "sdk/objects/appconst.h"


PostgresPlugin::PostgresPlugin(QObject *parent) : IocPlugin(parent)
{
  registerDependency((new DependencyMeta("postgresDatabase", CLASSMETA(PostgresDatabase), InstanceMode::Prototype))
                     ->setParam(F_TYPE, DBObjectItem::Database));
  registerDependency((new DependencyMeta("postgresTable", CLASSMETA(PostgresTable), InstanceMode::Prototype))
                     ->setParam(F_TYPE, DBObjectItem::Table));
  registerDependency((new DependencyMeta("postgresView", CLASSMETA(PostgresViewItem), InstanceMode::Prototype))
                     ->setParam(F_TYPE, DBObjectItem::View));
  registerDependency((new DependencyMeta("postgresFolder", CLASSMETA(PostgresFolderItem), InstanceMode::Prototype))
                     ->setParam(F_TYPE, DBObjectItem::Folder));
  registerDependency((new DependencyMeta("postgresTrigger", CLASSMETA(PostgresTriggerItem), InstanceMode::Prototype))
                     ->setParam(F_TYPE, DBObjectItem::Trigger));
  registerDependency((new DependencyMeta("postgresSequence", CLASSMETA(PostgresSequence), InstanceMode::Prototype))
                     ->setParam(F_TYPE, DBObjectItem::Sequence));
  registerDependency((new DependencyMeta("postgresFunction", CLASSMETA(PostgresFunctionItem), InstanceMode::Prototype))
                     ->setParam(F_TYPE, DBObjectItem::Procedure));
  registerDependency((new DependencyMeta("postgresPrimaryKey", CLASSMETA(PostgresPrimaryKey), InstanceMode::Prototype))
                     ->setParam(F_TYPE, DBObjectItem::PrimaryKey));
  registerDependency((new DependencyMeta("postgresForeignKey", CLASSMETA(PostgresForeignKey), InstanceMode::Prototype))
                     ->setParam(F_TYPE, DBObjectItem::ForeignKey));
  registerDependency((new DependencyMeta("postgresUnique", CLASSMETA(PostgresUniqueConstraint), InstanceMode::Prototype))
                     ->setParam(F_TYPE, DBObjectItem::UniqueConstraint));
  registerDependency((new DependencyMeta("postgresCheck", CLASSMETA(PostgresCheckConstraint), InstanceMode::Prototype))
                     ->setParam(F_TYPE, DBObjectItem::CheckConstraint));
}

QList<DBObjectItem::ItemType> PostgresPlugin::supportedTypes()
{
  QList<DBObjectItem::ItemType> types;
  types.append(DBObjectItem::Table);
  types.append(DBObjectItem::View);
  types.append(DBObjectItem::Sequence);
  types.append(DBObjectItem::Procedure);
  types.append(DBObjectItem::Trigger);
  return types;
}


QString PostgresPlugin::title()
{
    return "PostgreSQL database support plugin";
}

QString PostgresPlugin::author()
{
    return "Lev Alekseevskiy";
}

int PostgresPlugin::majorVersion()
{
    return 1;
}

int PostgresPlugin::minorVersion()
{
    return 0;
}

FeatureTypes PostgresPlugin::featureTypes()
{
    return FeatureType::DbmsObjects;
}

bool PostgresPlugin::driverSupported(QString driverName)
{
    return driverName.toUpper() == DRIVER_POSTGRES;
}

QString PostgresPlugin::driver()
{
    return DRIVER_POSTGRES;
}
