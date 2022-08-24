#include "firebirdplugin.h"
#include "objects/appconst.h"
#include "firebirdfolderitem.h"
#include "firebirddatabase.h"
#include "firebirdtable.h"
#include "firebirdsequence.h"
#include "firebirdprimarykey.h"
#include "firebirdforeignkey.h"
#include "firebirduniqueconstraint.h"
#include "firebirdcheckconstraint.h"
#include "firebirdview.h"
#include "firebirdtrigger.h"
#include "firebirdtriggerform.h"
#include "firebirdprocedureform.h"
#include "firebirdprocedure.h"
#include "forms/firebirddomainform.h"
#include "objects/firebirddomain.h"


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
  types.append(DBObjectItem::UserType);
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

  c->registerDependency(new DependencyMeta("firebirdPrimaryKeyItem", CLASSMETA(FirebirdPrimaryKey), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::PrimaryKey);
  c->registerDependency(new DependencyMeta("firebirdForeignKeyItem", CLASSMETA(FirebirdForeignKey), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::ForeignKey);
  c->registerDependency(new DependencyMeta("firebirdUniqueConstraintItem", CLASSMETA(FirebirdUniqueConstraint), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::UniqueConstraint);
  c->registerDependency(new DependencyMeta("firebirdCheckConstraintItem", CLASSMETA(FirebirdCheckConstraint), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::CheckConstraint);
  c->registerDependency(new DependencyMeta("firebirdViewItem", CLASSMETA(FirebirdView), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::View);
  c->registerDependency(new DependencyMeta("firebirdTrigger", CLASSMETA(FirebirdTrigger), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::Trigger);
  c->registerDependency(new DependencyMeta("firebirdProcedure", CLASSMETA(FirebirdProcedure), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::Procedure);
  c->registerDependency(new DependencyMeta("firebirdDomain", CLASSMETA(FirebirdDomain), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::UserType);

  c->registerDependency(new DependencyMeta("firebirdTriggerForm", CLASSMETA(FirebirdTriggerForm), InstanceMode::Singleton))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::Trigger);
  c->registerDependency(new DependencyMeta("firebirdProcedureForm", CLASSMETA(FirebirdProcedureForm), InstanceMode::Singleton))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::Procedure);
  c->registerDependency(new DependencyMeta("firebirdDomainForm", CLASSMETA(FirebirdDomainForm), InstanceMode::Singleton))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::UserType);
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
