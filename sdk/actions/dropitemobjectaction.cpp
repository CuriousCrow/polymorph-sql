#include "dropitemobjectaction.h"
#include <QDebug>
#include "core/localeventnotifier.h"
#include "utils/messagedialogs.h"

DropItemObjectAction::DropItemObjectAction() : BaseItemPopupAction(nullptr)
{
    setText(tr("Delete"));
    _supportedTypes.insert(DBObjectItem::View);
    _supportedTypes.insert(DBObjectItem::Table);
    _supportedTypes.insert(DBObjectItem::Procedure);
    _supportedTypes.insert(DBObjectItem::Trigger);
    _supportedTypes.insert(DBObjectItem::Sequence);
    _supportedTypes.insert(DBObjectItem::UserType);
}

void DropItemObjectAction::doAction()
{
    DBObjectItem* obj = context()->currentItem();
    ActionResult result = obj->deleteMe();
    if (!result.isSuccess()) {
        MessageDialogs::error(tr("Failed to delete DB object.\n\n") + result.description());
        return;
    }
    LocalEventNotifier::postLocalEvent(ItemDeleteEvent, obj->objectUrl().toString());
}
