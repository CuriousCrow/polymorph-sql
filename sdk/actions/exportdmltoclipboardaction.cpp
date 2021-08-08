#include "exportdmltoclipboardaction.h"
#include <QDebug>
#include <QGuiApplication>
#include <QClipboard>

ExportDMLToClipboardAction::ExportDMLToClipboardAction() : BaseItemPopupAction()
{
    setText(tr("Data to Clipboard"));
    _supportedTypes.insert(DBObjectItem::Table);
    _supportedTypes.insert(DBObjectItem::View);
    _supportedTypes.insert(DBObjectItem::Procedure);
    _supportedTypes.insert(DBObjectItem::Trigger);
    _supportedTypes.insert(DBObjectItem::Sequence);
}

void ExportDMLToClipboardAction::doAction()
{
    qDebug() << "DML export";
    DBObjectItem* curObj = context()->currentItem();
    curObj->refresh();
    QGuiApplication::clipboard()->setText(curObj->toDML());
}
