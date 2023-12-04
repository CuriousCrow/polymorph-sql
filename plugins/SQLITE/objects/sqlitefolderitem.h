#ifndef SQLITEFOLDERITEM_H
#define SQLITEFOLDERITEM_H

#include <QObject>
#include "objects/foldertreeitem.h"

/** Sqlite folder item */
class SqliteFolderItem : public FolderTreeItem
{
    Q_OBJECT
public:
    Q_INVOKABLE SqliteFolderItem();

    // FolderTreeItem interface
protected:
    virtual void loadChildren() override;
private:
    void loadSequences();
    void loadTriggers();
};

#endif // SQLITEFOLDERITEM_H
