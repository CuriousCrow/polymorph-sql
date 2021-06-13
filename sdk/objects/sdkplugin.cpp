#include "sdkplugin.h"
#include "dbtableitem.h"
#include "dbsequenceitem.h"
#include "dbviewitem.h"
#include "dbtriggeritem.h"
#include "dbprocedureitem.h"
#include "dbdatabaseitem.h"
#include "dbobjectitem.h"
#include "appconst.h"

#include "../forms/tableeditform.h"
#include "../forms/procedureeditform.h"
#include "../forms/sequenceeditform.h"
#include "../forms/triggereditform.h"
#include "../forms/vieweditdialog.h"
#include "../forms/checkconstrainteditform.h"
#include "../forms/connectioneditdialog.h"
#include "../forms/foreignkeyform.h"
#include "../forms/uniqueconstrainteditform.h"

#define BASE_DRIVER ""

SdkPlugin::SdkPlugin(QObject *parent) : IocPlugin(parent)
{

}

QList<DBObjectItem::ItemType> SdkPlugin::supportedTypes()
{
    QList<DBObjectItem::ItemType> types;
    types.append(DBObjectItem::Table);
    types.append(DBObjectItem::View);
    types.append(DBObjectItem::SystemTable);
    types.append(DBObjectItem::Sequence);
    types.append(DBObjectItem::Trigger);
    types.append(DBObjectItem::Procedure);
    return types;
}


QString SdkPlugin::title()
{
    return "Base SDK database support";
}

QString SdkPlugin::author()
{
    return "Lev Alekseevskiy";
}

int SdkPlugin::majorVersion()
{
    return 1;
}

int SdkPlugin::minorVersion()
{
    return 0;
}

FeatureTypes SdkPlugin::featureTypes()
{
    return FeatureTypes(FeatureType::DbmsForms | FeatureType::DbmsObjects);
}

bool SdkPlugin::driverSupported(QString driverName)
{
    return driverName.isEmpty();
}

QString SdkPlugin::driver()
{
    return "";
}

bool SdkPlugin::registerPlugin(DependencyContainer *c)
{
    c->registerDependency((new DependencyMeta("baseTableObject", CLASSMETA(DBTableItem), InstanceMode::Prototype))
                          ->setParam(F_DRIVER_NAME, BASE_DRIVER)
                          ->setParam(F_TYPE, DBObjectItem::Table));
    c->registerDependency((new DependencyMeta("baseViewObject", CLASSMETA(DBViewItem), InstanceMode::Prototype))
                          ->setParam(F_DRIVER_NAME, BASE_DRIVER)
                          ->setParam(F_TYPE, DBObjectItem::View));
    c->registerDependency((new DependencyMeta("baseTriggerObject", CLASSMETA(DBTriggerItem), InstanceMode::Prototype))
                          ->setParam(F_DRIVER_NAME, BASE_DRIVER)
                          ->setParam(F_TYPE, DBObjectItem::Trigger));
    c->registerDependency((new DependencyMeta("baseProcedureObject", CLASSMETA(DBProcedureItem), InstanceMode::Prototype))
                          ->setParam(F_DRIVER_NAME, BASE_DRIVER)
                          ->setParam(F_TYPE, DBObjectItem::Procedure));
    c->registerDependency((new DependencyMeta("baseSequenceObject", CLASSMETA(DBSequenceItem), InstanceMode::Prototype))
                          ->setParam(F_DRIVER_NAME, BASE_DRIVER)
                          ->setParam(F_TYPE, DBObjectItem::Sequence));

    c->registerDependency((new DependencyMeta("baseTableForm", CLASSMETA(TableEditForm), InstanceMode::Singleton))
                           ->setParam(F_TYPE, DBObjectItem::Table));
    c->registerDependency((new DependencyMeta("baseViewForm", CLASSMETA(ViewEditDialog), InstanceMode::Singleton))
                          ->setParam(F_TYPE, DBObjectItem::View));
    c->registerDependency((new DependencyMeta("baseProcedureForm", CLASSMETA(ProcedureEditForm), InstanceMode::Singleton))
                          ->setParam(F_TYPE, DBObjectItem::Procedure));
    c->registerDependency((new DependencyMeta("baseSequenceForm", CLASSMETA(SequenceEditForm), InstanceMode::Singleton))
                          ->setParam(F_TYPE, DBObjectItem::Sequence));
    c->registerDependency((new DependencyMeta("baseTriggerForm", CLASSMETA(TriggerEditForm), InstanceMode::Singleton))
                          ->setParam(F_TYPE, DBObjectItem::Trigger));
    c->registerDependency((new DependencyMeta("baseConnectionForm", CLASSMETA(ConnectionEditDialog), InstanceMode::Singleton))
                          ->setParam(F_TYPE, DBObjectItem::Database));
    c->registerDependency((new DependencyMeta("baseForeignKeyForm", CLASSMETA(ForeignKeyForm), InstanceMode::Singleton))
                          ->setParam(F_TYPE, DBObjectItem::ForeignKey));
    c->registerDependency((new DependencyMeta("baseCheckForm", CLASSMETA(CheckConstraintEditForm), InstanceMode::Singleton))
                          ->setParam(F_TYPE, DBObjectItem::CheckConstraint));
    c->registerDependency((new DependencyMeta("baseUniqueForm", CLASSMETA(UniqueConstraintEditForm), InstanceMode::Singleton))
                          ->setParam(F_TYPE, DBObjectItem::UniqueConstraint));
    return true;
}
