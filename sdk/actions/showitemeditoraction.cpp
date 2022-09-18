#include "showitemeditoraction.h"
#include <QDebug>
#include <QMessageBox>

ShowItemEditorAction::ShowItemEditorAction() : BaseItemPopupAction()
{
    setText(tr("Edit object"));
    _supportedTypes.insert(DBObjectItem::Table);
    _supportedTypes.insert(DBObjectItem::View);
    _supportedTypes.insert(DBObjectItem::SystemTable);
    _supportedTypes.insert(DBObjectItem::Procedure);
    _supportedTypes.insert(DBObjectItem::Trigger);
    _supportedTypes.insert(DBObjectItem::Sequence);
    _supportedTypes.insert(DBObjectItem::UserType);
}


void ShowItemEditorAction::doAction()
{
    qDebug() << "Show item editor action called";
    DBObjectItem* currentItem = context()->currentItem();
    if (!currentItem)
        return;

    AbstractDatabaseEditForm* editForm =
            _core->objectForm(currentItem->driverName(), (DBObjectItem::ItemType)currentItem->type());
    if (!editForm) {
      QMessageBox::warning(nullptr, TITLE_WARNING, tr("Edit form isn't supported yet"));
      return;
    }
    currentItem->refresh();
    editForm->setUserAction(AbstractDatabaseEditForm::Edit);
    editForm->setObjItem(currentItem);
    editForm->objectToForm();
    editForm->show();
}

void ShowItemEditorAction::updateState()
{
    BaseItemPopupAction::updateState();
    setVisible(context()->hasCurItem());
    setText(context()->isEditable() ? tr("Edit object") : tr("View object"));
}
