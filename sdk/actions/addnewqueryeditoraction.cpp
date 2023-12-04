#include "addnewqueryeditoraction.h"
#include <QDebug>
#include "core/extensionpoints.h"
#include "forms/queryeditorwindow.h"


AddNewQueryEditorAction::AddNewQueryEditorAction() : BaseContextAction()
{
    setText(tr("New query editor"));
}

void AddNewQueryEditorAction::updateState()
{
    setEnabled(true);
    setVisible(true);
}

QStringList AddNewQueryEditorAction::menuPath()
{
    QStringList pathList;
    pathList.append("Query");
    return pathList;
}

void AddNewQueryEditorAction::doAction()
{
    qDebug() << "Add new query editor";
    QueryEditorWindow* newQueryEditor = _core->dependency<QueryEditorWindow>(B_QUERY_EDITOR);
    _ds->tabWidget()->addTab(newQueryEditor, tr("Query"));
}


bool AddNewQueryEditorAction::supportsExtensionPoint(const ExtensionPoint &extensionPoint) const
{
  return extensionPoint.name() == EP_MAINWINDOW_MAINMENU;
}
