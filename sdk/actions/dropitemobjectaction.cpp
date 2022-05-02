#include "dropitemobjectaction.h"
#include <QDebug>
#include "core/localeventnotifier.h"

DropItemObjectAction::DropItemObjectAction() : BaseItemPopupAction(nullptr)
{
    setText(tr("Delete"));
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
        qDebug() << "Delete item failed";
    }
    LocalEventNotifier::postLocalEvent(ItemDeleteEvent, obj->objectUrl().toString());
}
