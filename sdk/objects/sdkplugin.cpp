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



SdkPlugin::SdkPlugin(QObject *parent) : IocPlugin(parent)
{
    registerDependency(new DependencyMeta("baseTableObject", CLASSMETA(DBTableItem), InstanceMode::Prototype));
    registerDependency(new DependencyMeta("baseViewObject", CLASSMETA(DBViewItem), InstanceMode::Prototype));
    registerDependency(new DependencyMeta("baseTriggerObject", CLASSMETA(DBTriggerItem), InstanceMode::Prototype));
    registerDependency(new DependencyMeta("baseProcedureObject", CLASSMETA(DBProcedureItem), InstanceMode::Prototype));
    registerDependency(new DependencyMeta("baseSequenceObject", CLASSMETA(DBSequenceItem), InstanceMode::Prototype));

    DependencyMeta* tableForm = new DependencyMeta("baseTableForm", CLASSMETA(TableEditForm), InstanceMode::Singleton);
    tableForm->insert(F_TYPE, DBObjectItem::Table);
    registerDependency(tableForm);
    DependencyMeta* viewForm = new DependencyMeta("baseViewForm", CLASSMETA(ViewEditDialog), InstanceMode::Singleton);
    viewForm->insert(F_TYPE, DBObjectItem::View);
    registerDependency(viewForm);
    DependencyMeta* procedureForm = new DependencyMeta("baseProcedureForm", CLASSMETA(ProcedureEditForm), InstanceMode::Singleton);
    procedureForm->insert(F_TYPE, DBObjectItem::Procedure);
    registerDependency(procedureForm);
    DependencyMeta* sequenceForm = new DependencyMeta("baseSequenceForm", CLASSMETA(SequenceEditForm), InstanceMode::Singleton);
    sequenceForm->insert(F_TYPE, DBObjectItem::Sequence);
    registerDependency(sequenceForm);
    DependencyMeta* triggerForm = new DependencyMeta("baseTriggerForm", CLASSMETA(TriggerEditForm), InstanceMode::Singleton);
    triggerForm->insert(F_TYPE, DBObjectItem::Trigger);
    registerDependency(triggerForm);
    DependencyMeta* connectionForm = new DependencyMeta("baseConnectionForm", CLASSMETA(ConnectionEditDialog), InstanceMode::Singleton);
    connectionForm->insert(F_TYPE, DBObjectItem::Database);
    registerDependency(connectionForm);
    DependencyMeta* foreignKeyForm = new DependencyMeta("baseForeignKeyForm", CLASSMETA(ForeignKeyForm), InstanceMode::Singleton);
    foreignKeyForm->insert(F_TYPE, DBObjectItem::ForeignKey);
    registerDependency(foreignKeyForm);
    DependencyMeta* checkConstraintForm = new DependencyMeta("baseCheckForm", CLASSMETA(CheckConstraintEditForm), InstanceMode::Singleton);
    checkConstraintForm->insert(F_TYPE, DBObjectItem::CheckConstraint);
    registerDependency(checkConstraintForm);
    DependencyMeta* uniqueConstraintForm = new DependencyMeta("baseUniqueForm", CLASSMETA(UniqueConstraintEditForm), InstanceMode::Singleton);
    uniqueConstraintForm->insert(F_TYPE, DBObjectItem::UniqueConstraint);
    registerDependency(uniqueConstraintForm);

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
