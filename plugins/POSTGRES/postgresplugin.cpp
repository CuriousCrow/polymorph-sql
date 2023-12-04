#include "postgresplugin.h"

#include "postgresconst.h"
#include "objects/appconst.h"
#include "objects/postgresdatabase.h"
#include "objects/postgrestable.h"
#include "objects/postgressequence.h"
#include "objects/postgrestrigger.h"
#include "objects/postgresfunction.h"
#include "objects/postgresview.h"
#include "objects/postgresfolderitem.h"
#include "objects/postgresprimarykey.h"
#include "objects/postgrescheckconstraint.h"
#include "objects/postgresforeignkey.h"
#include "objects/postgresuniqueconstraint.h"



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
    c->registerDependency(new DependencyMeta(B_POSTGRES_DATABASE, CLASSMETA(PostgresDatabase), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_POSTGRES)->setParam(F_TYPE, DBObjectItem::Database);
    c->registerDependency(new DependencyMeta(B_POSTGRES_TABLE, CLASSMETA(PostgresTable), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_POSTGRES)->setParam(F_TYPE, DBObjectItem::Table);
    c->registerDependency(new DependencyMeta(B_POSTGRES_VIEW, CLASSMETA(PostgresViewItem), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_POSTGRES)->setParam(F_TYPE, DBObjectItem::View);
    c->registerDependency(new DependencyMeta(B_POSTGRES_FOLDER, CLASSMETA(PostgresFolderItem), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_POSTGRES)->setParam(F_TYPE, DBObjectItem::Folder);
    c->registerDependency(new DependencyMeta(B_POSTGRES_TRIGGER, CLASSMETA(PostgresTriggerItem), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_POSTGRES)->setParam(F_TYPE, DBObjectItem::Trigger);
    c->registerDependency(new DependencyMeta(B_POSTGRES_SEQUENCE, CLASSMETA(PostgresSequence), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_POSTGRES)->setParam(F_TYPE, DBObjectItem::Sequence);
    c->registerDependency(new DependencyMeta(B_POSTGRES_PROCEDURE, CLASSMETA(PostgresFunctionItem), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_POSTGRES)->setParam(F_TYPE, DBObjectItem::Procedure);
    c->registerDependency(new DependencyMeta(B_POSTGRES_PK, CLASSMETA(PostgresPrimaryKey), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_POSTGRES)->setParam(F_TYPE, DBObjectItem::PrimaryKey);
    c->registerDependency(new DependencyMeta(B_POSTGRES_FK, CLASSMETA(PostgresForeignKey), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_POSTGRES)->setParam(F_TYPE, DBObjectItem::ForeignKey);
    c->registerDependency(new DependencyMeta(B_POSTGRES_UNIQUE, CLASSMETA(PostgresUniqueConstraint), InstanceMode::Prototype))
                       ->setParam(F_DRIVER_NAME, DRIVER_POSTGRES)->setParam(F_TYPE, DBObjectItem::UniqueConstraint);
    c->registerDependency(new DependencyMeta(B_POSTGRES_CHECK, CLASSMETA(PostgresCheckConstraint), InstanceMode::Prototype))
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
