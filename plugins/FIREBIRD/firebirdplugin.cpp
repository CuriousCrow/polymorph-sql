#include "firebirdplugin.h"
#include "objects/appconst.h"
#include "objects/firebirdfolderitem.h"
#include "objects/firebirddatabase.h"
#include "objects/firebirdtable.h"
#include "objects/firebirdsequence.h"
#include "objects/firebirdprimarykey.h"
#include "objects/firebirdforeignkey.h"
#include "objects/firebirduniqueconstraint.h"
#include "objects/firebirdcheckconstraint.h"
#include "objects/firebirdview.h"
#include "objects/firebirdtrigger.h"
#include "objects/firebirdprocedure.h"
#include "objects/firebirddomain.h"
#include "forms/firebirdtriggerform.h"
#include "forms/firebirdprocedureform.h"
#include "forms/firebirddomainform.h"
#include "firebirdtypeprovider.h"
#include "firebirdconst.h"


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
  c->registerDependency(new DependencyMeta(B_FIREBIRD_DATABASE, CLASSMETA(FirebirdDatabase), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::Database);
  c->registerDependency(new DependencyMeta(B_FIREBIRD_FOLDER, CLASSMETA(FirebirdFolderItem), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::Folder);
  c->registerDependency(new DependencyMeta(B_FIREBIRD_TABLE, CLASSMETA(FirebirdTable), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::Table);
  c->registerDependency(new DependencyMeta(B_FIREBIRD_SEQUENCE, CLASSMETA(FirebirdSequence), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::Sequence);

  c->registerDependency(new DependencyMeta(B_FIREBIRD_PRIMARY_KEY, CLASSMETA(FirebirdPrimaryKey), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::PrimaryKey);
  c->registerDependency(new DependencyMeta(B_FIREBIRD_FOREIGN_KEY, CLASSMETA(FirebirdForeignKey), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::ForeignKey);
  c->registerDependency(new DependencyMeta(B_FIREBIRD_UNIQUE_CONSTRAINT, CLASSMETA(FirebirdUniqueConstraint), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::UniqueConstraint);
  c->registerDependency(new DependencyMeta(B_FIREBIRD_CHECK_CONSTRAINT, CLASSMETA(FirebirdCheckConstraint), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::CheckConstraint);
  c->registerDependency(new DependencyMeta(B_FIREBIRD_VIEW, CLASSMETA(FirebirdView), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::View);
  c->registerDependency(new DependencyMeta(B_FIREBIRD_TRIGGER, CLASSMETA(FirebirdTrigger), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::Trigger);
  c->registerDependency(new DependencyMeta(B_FIREBIRD_PROCEDURE, CLASSMETA(FirebirdProcedure), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::Procedure);
  c->registerDependency(new DependencyMeta(B_FIREBIRD_DOMAIN, CLASSMETA(FirebirdDomain), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::UserType);

  c->registerDependency(new DependencyMeta(B_FIREBIRD_TRIGGER_FORM, CLASSMETA(FirebirdTriggerForm), InstanceMode::Singleton))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::Trigger);
  c->registerDependency(new DependencyMeta(B_FIREBIRD_PROCEDURE_FORM, CLASSMETA(FirebirdProcedureForm), InstanceMode::Singleton))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::Procedure);
  c->registerDependency(new DependencyMeta(B_FIREBIRD_DOMAIN_FORM, CLASSMETA(FirebirdDomainForm), InstanceMode::Singleton))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD)->setParam(F_TYPE, DBObjectItem::UserType);

  c->registerDependency(new DependencyMeta(B_FIREBIRD_TYPE_PROVIDER, CLASSMETA(FirebirdTypeProvider), InstanceMode::Singleton))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD);
  c->registerDependency(new DependencyMeta(B_FIREBIRD_ARG_MODEL, CLASSMETA(ArgumentTableModel), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_FIREBIRD);
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
