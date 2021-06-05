#ifndef FIREBIRDFOLDERITEM_H
#define FIREBIRDFOLDERITEM_H

#include "sdk/objects/foldertreeitem.h"
#include <QObject>

class FirebirdFolderItem : public FolderTreeItem
{
    Q_OBJECT
public:
    FirebirdFolderItem(QObject* parent = nullptr);

    // FolderTreeItem interface
protected:
    virtual void loadChildren() override;
};

#endif // FIREBIRDFOLDERITEM_H
