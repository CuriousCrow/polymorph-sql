#include "postgresplugin.h"
#include "objects/appconst.h"
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
#include "objects/appconst.h"


PostgresPlugin::PostgresPlugin(QObject *parent) : IocPlugin(parent)
{

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

bool PostgresPlugin::registerPlugin(DependencyContainer *c)
{
    c->registerDependency(new DependencyMeta("postgresDatabase", CLASSMETA(PostgresDatabase), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_POSTGRES)->setParam(F_TYPE, DBObjectItem::Database);
    c->registerDependency(new DependencyMeta("postgresTable", CLASSMETA(PostgresTable), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_POSTGRES)->setParam(F_TYPE, DBObjectItem::Table);
    c->registerDependency(new DependencyMeta("postgresView", CLASSMETA(PostgresViewItem), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_POSTGRES)->setParam(F_TYPE, DBObjectItem::View);
    c->registerDependency(new DependencyMeta("postgresFolder", CLASSMETA(PostgresFolderItem), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_POSTGRES)->setParam(F_TYPE, DBObjectItem::Folder);
    c->registerDependency(new DependencyMeta("postgresTrigger", CLASSMETA(PostgresTriggerItem), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_POSTGRES)->setParam(F_TYPE, DBObjectItem::Trigger);
    c->registerDependency(new DependencyMeta("postgresSequence", CLASSMETA(PostgresSequence), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_POSTGRES)->setParam(F_TYPE, DBObjectItem::Sequence);
    c->registerDependency(new DependencyMeta("postgresFunction", CLASSMETA(PostgresFunctionItem), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_POSTGRES)->setParam(F_TYPE, DBObjectItem::Procedure);
    c->registerDependency(new DependencyMeta("postgresPrimaryKey", CLASSMETA(PostgresPrimaryKey), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_POSTGRES)->setParam(F_TYPE, DBObjectItem::PrimaryKey);
    c->registerDependency(new DependencyMeta("postgresForeignKey", CLASSMETA(PostgresForeignKey), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_POSTGRES)->setParam(F_TYPE, DBObjectItem::ForeignKey);
    c->registerDependency(new DependencyMeta("postgresUnique", CLASSMETA(PostgresUniqueConstraint), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_POSTGRES)->setParam(F_TYPE, DBObjectItem::UniqueConstraint);
    c->registerDependency(new DependencyMeta("postgresCheck", CLASSMETA(PostgresCheckConstraint), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_POSTGRES)->setParam(F_TYPE, DBObjectItem::CheckConstraint);
    return true;
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
