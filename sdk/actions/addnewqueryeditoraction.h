#ifndef ADDNEWQUERYEDITORACTION_H
#define ADDNEWQUERYEDITORACTION_H

#include "core/basecontextaction.h"
#include "core/datastore.h"
#include "core/core.h"
#include <QObject>
#include "core/extensionpoints.h"
#include "core/extensions.h"

class AddNewQueryEditorAction : public BaseContextAction, public MainMenuItem, public AbstractExtension
{
    Q_OBJECT
public:
    Q_INVOKABLE AddNewQueryEditorAction();
    INJECT(DataStore*, ds)
    INJECT(Core*, core)

    // AbstractContextAction interface
protected slots:
    virtual void updateState() override;

    // MainMenuItem interface
public:
    virtual QStringList menuPath() override;

    // BaseContextAction interface
public slots:
    virtual void doAction() override;

    // AbstractExtension interface
public:
    virtual bool supportsExtensionPoint(const ExtensionPoint &extensionPoint) const override;
};

#endif // ADDNEWQUERYEDITORACTION_H
