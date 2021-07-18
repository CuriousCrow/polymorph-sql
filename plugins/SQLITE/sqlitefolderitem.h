#ifndef SQLITEFOLDERITEM_H
#define SQLITEFOLDERITEM_H

#include "objects/foldertreeitem.h"
#include <QObject>

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
    void loadProcedures();
};

#endif // SQLITEFOLDERITEM_H
