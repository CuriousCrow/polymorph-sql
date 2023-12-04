#ifndef RELOADFOLDERITEMSACTION_H
#define RELOADFOLDERITEMSACTION_H

#include <QObject>
#include "core/basecontextaction.h"
#include "core/datastore.h"
#include "core/dependencycontainer.h"

class ReloadFolderItemsAction : public BaseItemPopupAction
{
    Q_OBJECT
public:
    Q_INVOKABLE ReloadFolderItemsAction();
    INJECT(DataStore*, ds)

    // BaseContextAction interface
public slots:
    virtual void doAction() override;
};

#endif // RELOADFOLDERITEMSACTION_H
