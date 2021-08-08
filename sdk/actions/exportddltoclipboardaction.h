#ifndef EXPORTDDLTOCLIPBOARDACTION_H
#define EXPORTDDLTOCLIPBOARDACTION_H

#include <QObject>
#include "core/basecontextaction.h"

class ExportDDLToClipboardAction : public BaseItemPopupAction
{
    Q_OBJECT
public:
    Q_INVOKABLE ExportDDLToClipboardAction();

    // BaseContextAction interface
public slots:
    virtual void doAction() override;
};

#endif // EXPORTDDLTOCLIPBOARDACTION_H
