#include "showitemeditoraction.h"
#include <QDebug>
#include <QMessageBox>

ShowItemEditorAction::ShowItemEditorAction() : BaseItemPopupAction()
{
    setText("Edit object");
    _supportedTypes.insert(DBObjectItem::Table);
    _supportedTypes.insert(DBObjectItem::View);
    _supportedTypes.insert(DBObjectItem::Procedure);
    _supportedTypes.insert(DBObjectItem::Trigger);
    _supportedTypes.insert(DBObjectItem::Sequence);
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
      QMessageBox::warning(nullptr, TITLE_WARNING, "Edit form isn't supported yet");
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
    setText(context()->currentItem()->isEditable() ? tr("Edit object") : tr("View object"));
}
