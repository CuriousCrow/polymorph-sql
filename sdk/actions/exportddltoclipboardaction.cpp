#include "exportddltoclipboardaction.h"
#include <QMessageBox>
#include <QGuiApplication>
#include <QClipboard>

ExportDDLToClipboardAction::ExportDDLToClipboardAction() : BaseItemPopupAction()
{
    setText(tr("DDL to Clipboard"));
    _supportedTypes.insert(DBObjectItem::Table);
    _supportedTypes.insert(DBObjectItem::View);
    _supportedTypes.insert(DBObjectItem::Procedure);
    _supportedTypes.insert(DBObjectItem::Trigger);
    _supportedTypes.insert(DBObjectItem::Sequence);
}

void ExportDDLToClipboardAction::doAction()
{
    DBObjectItem* obj = context()->currentItem();
    bool refreshSuccess = obj->refresh();
    if (!refreshSuccess) {
        QMessageBox::warning(nullptr, "Error", "Object refresh failed");
        return;
    }
    QGuiApplication::clipboard()->setText(obj->toDDL());
}
