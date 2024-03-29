#include "showdatabaseexporteditoraction.h"
#include <QDebug>
#include "core/extensionpoints.h"
#include "forms/databaseexportform.h"

ShowDatabaseExportEditorAction::ShowDatabaseExportEditorAction() : BaseContextAction(nullptr)
{
    setText(tr("Export database"));
    setProperty("menuPath", "Tools");
}


void ShowDatabaseExportEditorAction::updateState()
{
    BaseUserContext* con = static_cast<BaseUserContext*>(_context);
    setEnabled(con->type() == DBObjectItem::Database);
}

void ShowDatabaseExportEditorAction::doAction()
{
    qDebug() << "Show database export form";
    QVariantHash p;
    DatabaseExportForm* form = _core->dependency<DatabaseExportForm>(p);
    if (form) {
        form->show();
    }
    else {
        qWarning() << "Cant load export form";
    }
}


QStringList ShowDatabaseExportEditorAction::menuPath()
{
    QStringList path;
    path << "Tools";
    return path;
}


bool ShowDatabaseExportEditorAction::supportsExtensionPoint(const ExtensionPoint &extensionPoint) const
{
  return extensionPoint.name() == EP_MAINWINDOW_MAINMENU;
}
