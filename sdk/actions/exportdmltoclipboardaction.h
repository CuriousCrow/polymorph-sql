#ifndef EXPORTDMLTOCLIPBOARDACTION_H
#define EXPORTDMLTOCLIPBOARDACTION_H

#include <QObject>
#include "core/basecontextaction.h"

class ExportDMLToClipboardAction : public BaseItemPopupAction
{
    Q_OBJECT
public:
    Q_INVOKABLE ExportDMLToClipboardAction();

    // BaseContextAction interface
public slots:
    virtual void doAction() override;
};

#endif // EXPORTDMLTOCLIPBOARDACTION_H
