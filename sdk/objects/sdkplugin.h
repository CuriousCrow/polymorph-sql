#ifndef SDKPLUGIN_H
#define SDKPLUGIN_H

#include "../core/iocplugin.h"
#include <QObject>

#define B_TABLE "baseTableObject"
#define B_VIEW "baseViewObject"
#define B_TRIGGER "baseTriggerObject"
#define B_PROCEDURE "baseProcedureObject"
#define B_SEQUENCE "baseSequenceObject"
#define B_PRIMARY_KEY "basePrimaryKey"

#define B_TABLE_FORM "baseTableForm"
#define B_SYSTEM_TABLE_FORM "baseSytemTableForm"
#define B_VIEW_FORM "baseViewForm"
#define B_PROCEDURE_FORM "baseProcedureForm"
#define B_SEQUENCE_FORM "baseSequenceForm"
#define B_TRIGGER_FORM "baseTriggerForm"
#define B_CONNECTION_FORM "baseConnectionForm"
#define B_FOREIGN_KEY_FORM "baseForeignKeyForm"
#define B_CHECK_FORM "baseCheckForm"
#define B_PRIMARY_KEY_FORM "basePrimaryKeyForm"
#define B_UNIQUE_FORM "baseUniqueForm"
#define B_QUERY_HISTORY_FORM "queryHistoryForm"
#define B_TABLE_BROWSER_FORM "tableBrowserForm"

#define B_KNOWLEDGE_BASE "kb"
#define B_HELPLOOKUP_PROVIDER "helpLookupProvider"
#define B_SQL_SYNTAX_HIGHLIGHTER "sqlSyntaxHighlighter"
#define B_SQL_COMPLETER_SUPPORT "sqlCompleterSupport"

#define B_BASE_COLUMN_MODEL "baseColumnModel"

#define B_TABLE_FILTER_REMOVE_ACTION "removeTableFilter"

#define B_TOGGLE_QUERY_LINE_COMMENTS "toggleQueryCommentsKey"
#define B_GENERATE_TABLE_ALIAS "generateTableAlias"

class SdkPlugin : public IocPlugin
{
    Q_OBJECT
public:
    SdkPlugin(QObject *parent = nullptr);

    // IocPlugin interface
public:
    virtual QList<DBObjectItem::ItemType> supportedTypes() override;
    virtual bool registerPlugin(DependencyContainer *c) override;

    // AbstractPlugin interface
public:
    virtual QString title() override;
    virtual QString author() override;
    virtual int majorVersion() override;
    virtual int minorVersion() override;
    virtual FeatureTypes featureTypes() override;
    virtual bool driverSupported(QString driverName) override;
    virtual QString driver() override;
};

#endif // SDKPLUGIN_H
