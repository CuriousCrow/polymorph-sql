#ifndef SDKPLUGIN_H
#define SDKPLUGIN_H

#include "../core/iocplugin.h"
#include <QObject>

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
