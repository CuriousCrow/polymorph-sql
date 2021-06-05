#ifndef POSTGRESFOLDERITEM_H
#define POSTGRESFOLDERITEM_H

#include "sdk/objects/foldertreeitem.h"
#include <QObject>

class PostgresFolderItem : public FolderTreeItem
{
    Q_OBJECT
public:
    PostgresFolderItem(QObject* parent = nullptr);

    // FolderTreeItem interface
protected:
    virtual void loadChildren() override;
private:
    void loadSequences();
    void loadTriggers();
    void loadProcedures();
};

#endif // POSTGRESFOLDERITEM_H
