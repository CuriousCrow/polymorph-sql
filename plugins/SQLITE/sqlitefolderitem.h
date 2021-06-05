#ifndef SQLITEFOLDERITEM_H
#define SQLITEFOLDERITEM_H

#include "sdk/objects/foldertreeitem.h"
#include <QObject>

class SqliteFolderItem : public FolderTreeItem
{
    Q_OBJECT
public:
    SqliteFolderItem(QObject* parent = nullptr);

    // FolderTreeItem interface
protected:
    virtual void loadChildren() override;
private:
    void loadSequences();
    void loadTriggers();
    void loadProcedures();
};

#endif // SQLITEFOLDERITEM_H
