#include "removetablefilteraction.h"
#include <QDebug>
#include "core/extensionpoints.h"

RemoveTableFilterAction::RemoveTableFilterAction() : UniSqlTableModelAction()
{
  setText(tr("Remove filter 2"));
  setObjectName("RemoveTableFilterAction instance");
  connect(this, &RemoveTableFilterAction::triggered, this, &RemoveTableFilterAction::doAction);
}


bool RemoveTableFilterAction::supportsExtensionPoint(const ExtensionPoint &extensionPoint) const
{
  if (extensionPoint.name() == EP_TABLEBROWSER_FILTER_POPUP) {
    return true;
  }
  return false;
}

void RemoveTableFilterAction::doAction()
{
  qDebug() << "Hello from RemoveTableFilterAction";
}
