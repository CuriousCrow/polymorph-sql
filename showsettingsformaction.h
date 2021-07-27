#ifndef SHOWSETTINGSFORMACTION_H
#define SHOWSETTINGSFORMACTION_H

#include "core/basecontextaction.h"
#include <QObject>

class ShowSettingsFormAction : public BaseContextAction, public MainMenuItem
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
};

#endif // SHOWSETTINGSFORMACTION_H
