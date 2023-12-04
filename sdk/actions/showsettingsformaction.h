#ifndef SHOWSETTINGSFORMACTION_H
#define SHOWSETTINGSFORMACTION_H

#include "core/basecontextaction.h"
#include <QObject>
#include "core/core.h"
#include "core/extensions.h"

class ShowSettingsFormAction : public BaseContextAction, public MainMenuItem, public AbstractExtension
{
    Q_OBJECT
public:
    Q_INVOKABLE ShowSettingsFormAction();
    INJECT(Core*, core)

    // AbstractContextAction interface
protected slots:
    virtual void updateState() override;

    // BaseContextAction interface
public slots:
    virtual void doAction() override;

    // MainMenuItem interface
public:
    virtual QStringList menuPath() override;

    // AbstractExtension interface
public:
    virtual bool supportsExtensionPoint(const ExtensionPoint &extensionPoint) const override;
};

#endif // SHOWSETTINGSFORMACTION_H
