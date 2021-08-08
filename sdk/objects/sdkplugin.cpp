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

#include "core/qknowledgebase.h"
#include "core/sqlhelplookupprovider.h"
#include "tools/qsqlsyntaxhighlighter.h"

#include "models/sqlcolumnmodel.h"

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
    //Database objects
    c->registerDependency(B_TABLE, CLASSMETA(DBTableItem), InstanceMode::Prototype)
                          ->setParam(F_DRIVER_NAME, DRIVER_BASE)->setParam(F_TYPE, DBObjectItem::Table);
    c->registerDependency(B_VIEW, CLASSMETA(DBViewItem), InstanceMode::Prototype)
                          ->setParam(F_DRIVER_NAME, DRIVER_BASE)->setParam(F_TYPE, DBObjectItem::View);
    c->registerDependency(B_TRIGGER, CLASSMETA(DBTriggerItem), InstanceMode::Prototype)
                          ->setParam(F_DRIVER_NAME, DRIVER_BASE)->setParam(F_TYPE, DBObjectItem::Trigger);
    c->registerDependency(B_PROCEDURE, CLASSMETA(DBProcedureItem), InstanceMode::Prototype)
                          ->setParam(F_DRIVER_NAME, DRIVER_BASE)->setParam(F_TYPE, DBObjectItem::Procedure);
    c->registerDependency(B_SEQUENCE, CLASSMETA(DBSequenceItem), InstanceMode::Prototype)
                          ->setParam(F_DRIVER_NAME, DRIVER_BASE)->setParam(F_TYPE, DBObjectItem::Sequence);

    //Tools
    c->registerDependency(B_HELPLOOKUP_PROVIDER, CLASSMETA(SqlHelpLookupProvider), InstanceMode::Prototype);
    c->registerDependency(B_SQL_SYNTAX_HIGHLIGHTER, CLASSMETA(QSqlSyntaxHighlighter), InstanceMode::Singleton);

    //Models
    c->registerDependency(B_BASE_COLUMN_MODEL, CLASSMETA(SqlColumnModel), InstanceMode::Prototype);

    //Object Forms
    c->registerDependency(B_TABLE_FORM, CLASSMETA(TableEditForm), InstanceMode::Singleton)
                           ->setParam(F_TYPE, DBObjectItem::Table);
    c->registerDependency(B_VIEW_FORM, CLASSMETA(ViewEditDialog), InstanceMode::Singleton)
                          ->setParam(F_TYPE, DBObjectItem::View);
    c->registerDependency(B_PROCEDURE_FORM, CLASSMETA(ProcedureEditForm), InstanceMode::Singleton)
                          ->setParam(F_TYPE, DBObjectItem::Procedure);
    c->registerDependency(B_SEQUENCE_FORM, CLASSMETA(SequenceEditForm), InstanceMode::Singleton)
                          ->setParam(F_TYPE, DBObjectItem::Sequence);
    c->registerDependency(B_TRIGGER_FORM, CLASSMETA(TriggerEditForm), InstanceMode::Singleton)
                          ->setParam(F_TYPE, DBObjectItem::Trigger);
    c->registerDependency(B_CONNECTION_FORM, CLASSMETA(ConnectionEditDialog), InstanceMode::Singleton)
                          ->setParam(F_TYPE, DBObjectItem::Database);
    c->registerDependency(B_FOREIGN_KEY_FORM, CLASSMETA(ForeignKeyForm), InstanceMode::Prototype)
                          ->setParam(F_TYPE, DBObjectItem::ForeignKey);
    c->registerDependency(B_CHECK_FORM, CLASSMETA(CheckConstraintEditForm), InstanceMode::Prototype)
                          ->setParam(F_TYPE, DBObjectItem::CheckConstraint);
    c->registerDependency(B_PRIMARY_KEY_FORM, CLASSMETA(UniqueConstraintEditForm), InstanceMode::Prototype)
                          ->setParam(F_TYPE, DBObjectItem::PrimaryKey);
    c->registerDependency(B_UNIQUE_FORM, CLASSMETA(UniqueConstraintEditForm), InstanceMode::Prototype)
                          ->setParam(F_TYPE, DBObjectItem::UniqueConstraint);
    return true;
}
