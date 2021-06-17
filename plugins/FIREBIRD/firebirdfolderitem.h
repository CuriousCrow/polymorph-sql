#ifndef FIREBIRDFOLDERITEM_H
#define FIREBIRDFOLDERITEM_H

#include "objects/foldertreeitem.h"
#include <QObject>

class FirebirdFolderItem : public FolderTreeItem
{
    Q_OBJECT
public:
    Q_INVOKABLE FirebirdFolderItem();

    // FolderTreeItem interface
protected:
    virtual void loadChildren() override;
};

#endif // FIREBIRDFOLDERITEM_H
