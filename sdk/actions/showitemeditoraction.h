#ifndef SHOWITEMEDITORACTION_H
#define SHOWITEMEDITORACTION_H

#include <QObject>
#include "core/basecontextaction.h"
#include "core/core.h"

class ShowItemEditorAction : public BaseItemPopupAction
{
    Q_OBJECT
public:
    Q_INVOKABLE ShowItemEditorAction();
    INJECT(Core*, core)

    // BaseContextAction interface
public slots:
    virtual void doAction() override;

    // AbstractContextAction interface
protected slots:
    virtual void updateState() override;
};

#endif // SHOWITEMEDITORACTION_H
