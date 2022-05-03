#ifndef SHOWCREATEFORMACTION_H
#define SHOWCREATEFORMACTION_H

#include <QObject>
#include "core/basecontextaction.h"

class ShowCreateFormAction : public BaseItemPopupAction
{
    Q_OBJECT
public:
    Q_INVOKABLE ShowCreateFormAction();
    INJECT(Core*, core)

    // BaseContextAction interface
public slots:
    virtual void doAction() override;
};

#endif // SHOWCREATEFORMACTION_H
