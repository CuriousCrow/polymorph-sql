#include "reloadfolderitemsaction.h"
#include "objects/dbobjectitem.h"
#include <QDebug>

ReloadFolderItemsAction::ReloadFolderItemsAction() : BaseItemPopupAction()
{
    setText(tr("Refresh items"));
    _supportedTypes.insert(DBObjectItem::Folder);
}


void ReloadFolderItemsAction::doAction()
{
    DBObjectItem* curObj = context()->currentItem();
    Q_ASSERT(curObj->type() == DBObjectItem::Folder);

    _ds->structureModel()->deleteChildren(curObj);
    qDebug() << "Folder" << curObj->caption() << "refresh request";
    curObj->reloadChildren();

    QModelIndex folderIdx = _ds->structureModel()->indexByItem(curObj);
    emit _ds->structureModel()->dataChanged(folderIdx, folderIdx);
}
