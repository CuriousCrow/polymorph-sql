#include "switchconnectedaction.h"
#include "../core/localeventnotifier.h"

#define T_CONNECT "Connect database"
#define T_DISCONNECT "Disconnect database"

SwitchConnectedAction::SwitchConnectedAction() : BaseItemPopupAction()
{
  _supportedTypes.insert(DBObjectItem::Database);
}


void SwitchConnectedAction::doAction()
{
  LocalEventNotifier::postLocalEvent(
        SwitchConnectedEvent,
        context()->currentItem()->objectUrl().toString());
}

void SwitchConnectedAction::updateState()
{
  setText(isConnected() ? T_DISCONNECT : T_CONNECT);
  BaseItemPopupAction::updateState();
}

bool SwitchConnectedAction::isConnected()
{
  return context()->currentItem()->hasChildren();
}
