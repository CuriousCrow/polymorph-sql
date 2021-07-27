#include "dropitemobjectaction.h"
#include <QDebug>

DropItemObjectAction::DropItemObjectAction() : BaseItemPopupAction(nullptr)
{
    setText("Delete");
    _supportedTypes.insert(DBObjectItem::View);
    _supportedTypes.insert(DBObjectItem::Table);
    _supportedTypes.insert(DBObjectItem::Procedure);
    _supportedTypes.insert(DBObjectItem::Trigger);
    _supportedTypes.insert(DBObjectItem::Sequence);
}

void DropItemObjectAction::doAction()
{
    DBObjectItem* obj = context()->currentItem();
    ActionResult result = obj->deleteMe();
    if (!result.isSuccess()) {
        qDebug() << "Ne shmogla";
    }
}
