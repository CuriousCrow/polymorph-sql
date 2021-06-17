#ifndef MYSQLFOLDERITEM_H
#define MYSQLFOLDERITEM_H

#include "objects/foldertreeitem.h"
#include <QObject>

class MysqlFolderItem : public FolderTreeItem
{
    Q_OBJECT
public:
    Q_INVOKABLE MysqlFolderItem();

    // FolderTreeItem interface
protected:
    virtual void loadChildren() override;
};

#endif // MYSQLFOLDERITEM_H
