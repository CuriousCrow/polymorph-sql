#ifndef MYSQLFOLDERITEM_H
#define MYSQLFOLDERITEM_H

#include "sdk/objects/foldertreeitem.h"
#include <QObject>

class MysqlFolderItem : public FolderTreeItem
{
    Q_OBJECT
public:
    MysqlFolderItem(QObject* parent = nullptr);

    // FolderTreeItem interface
protected:
    virtual void loadChildren() override;
};

#endif // MYSQLFOLDERITEM_H
