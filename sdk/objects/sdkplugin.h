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
#define B_VIEW_FORM "baseViewForm"
#define B_PROCEDURE_FORM "baseProcedureForm"
#define B_SEQUENCE_FORM "baseSequenceForm"
#define B_TRIGGER_FORM "baseTriggerForm"
#define B_CONNECTION_FORM "baseConnectionForm"
#define B_FOREIGN_KEY_FORM "baseForeignKeyForm"
#define B_CHECK_FORM "baseCheckForm"
#define B_PRIMARY_KEY_FORM "basePrimaryKeyForm"
#define B_UNIQUE_FORM "baseUniqueForm"


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
