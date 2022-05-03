#include "showcreateformaction.h"
#include <QDebug>
#include <QMessageBox>
#include "objects/foldertreeitem.h"

ShowCreateFormAction::ShowCreateFormAction() : BaseItemPopupAction()
{
    setText(tr("Create object"));
    _supportedTypes.insert(DBObjectItem::Folder);
}


void ShowCreateFormAction::doAction()
{
    qDebug() << "Create form action";
    DBObjectItem* currentItem = context()->currentItem();

    if (!currentItem) {
      qWarning() << "No item selected";
      return;
    }
    else if (currentItem->type() != DBObjectItem::Folder) {
      qWarning() << "Create item action: Not folder item";
      return;
    }

    FolderTreeItem* folderItem = static_cast<FolderTreeItem*>(currentItem);
    QString driverName = folderItem->driverName();
    AbstractDatabaseEditForm* createForm = _core->objectForm(driverName, folderItem->childrenType());
    DBObjectItem* newItem = _core->newObjInstance(driverName, folderItem->childrenType());

    newItem->setParentUrl(folderItem->objectUrl());
    createForm->setObjItem(newItem);
    createForm->setUserAction(AbstractDatabaseEditForm::Create);
    createForm->objectToForm();
    createForm->show();
}
