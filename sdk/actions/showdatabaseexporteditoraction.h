#ifndef SHOWDATABASEEXPORTEDITORACTION_H
#define SHOWDATABASEEXPORTEDITORACTION_H

#include "core/basecontextaction.h"
#include "forms/databaseexportform.h"
#include "core/baseusercontext.h"
#include "core/core.h"
#include <QObject>
#include "core/extensionpoints.h"
#include "core/extensions.h"

class ShowDatabaseExportEditorAction : public BaseContextAction, public MainMenuItem, public AbstractExtension
{
    Q_OBJECT
public:
    Q_INVOKABLE ShowDatabaseExportEditorAction();
    INJECT_INITIALIZE(BaseUserContext*, _context, context)
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

#endif // SHOWDATABASEEXPORTEDITORACTION_H
