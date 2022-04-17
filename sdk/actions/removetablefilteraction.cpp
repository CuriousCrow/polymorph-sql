#include "removetablefilteraction.h"
#include <QDebug>
#include "core/extensionpoints.h"

RemoveTableFilterAction::RemoveTableFilterAction() : UniSqlTableFilterAction()
{
  setText(tr("Remove filter"));
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
  int row = _listView->currentIndex().row();
  if (row >= 0) {
    _filterModel->removeFilter(row);
  }
}
