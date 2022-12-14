#include "basecontextaction.h"
#include "core/extensionpoints.h"

BaseContextAction::BaseContextAction(QObject *parent) : AbstractContextAction(parent)
{
    connect(this, &BaseContextAction::triggered, this, &BaseContextAction::doAction);
}

void BaseContextAction::inject_by_context(BaseUserContext *context)
{
    setContext(context);
}

BaseUserContext *BaseContextAction::context()
{
    return static_cast<BaseUserContext*>(_context);
}

void BaseContextAction::doAction()
{
    //Should be overriden with real action code
}


BaseItemPopupAction::BaseItemPopupAction(QObject *parent) : BaseContextAction(parent)
{
}

void BaseItemPopupAction::updateState()
{
    setVisible(_supportedTypes.contains(context()->type()));
}


bool BaseItemPopupAction::supportsExtensionPoint(const ExtensionPoint &extensionPoint) const
{
  return extensionPoint.name() == EP_MAINWINDOW_STRUCTURE_POPUP;
}
