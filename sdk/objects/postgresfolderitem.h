#ifndef POSTGRESFOLDERITEM_H
#define POSTGRESFOLDERITEM_H

#include "foldertreeitem.h"
#include <QObject>

class PostgresFolderItem : public FolderTreeItem
{
    Q_OBJECT
public:
    PostgresFolderItem(QObject* parent = nullptr);
};

#endif // POSTGRESFOLDERITEM_H
