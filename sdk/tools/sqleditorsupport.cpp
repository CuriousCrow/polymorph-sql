#include "sqleditorsupport.h"
#include "tools/keysequenceinterceptor.h"
#include "actions/queryeditorkeysequences.h"

SqlEditorSupport::SqlEditorSupport() : QObject()
{
  _keyInterceptor = new KeySequenceInterceptor(this);
  HelpKeyHandler* helpKeyHandler = new HelpKeyHandler();
  connect(helpKeyHandler, &HelpKeyHandler::keySignal,
          this, &SqlEditorSupport::onHelpKey);
  _keyInterceptor->registerHandler(helpKeyHandler);

  _extensionPoints.insert(ExtensionPoint(EP_QUERYEDITOR_KEYSEQUENCE, CLASS(AbstractKeySequenceHandler), "Test key sequence handler", false));
}

void SqlEditorSupport::inject_sqlCompleterSupport_into_form(SimpleSqlCompleterSupport *completerSupport)
{
  _completerSupport = completerSupport;
}

void SqlEditorSupport::inject_helpLookupProvider(SqlHelpLookupProvider *lookupProvider)
{
  _helpLookupProvider = lookupProvider;
//  _helpLookupProvider->setParent(this);
}

void SqlEditorSupport::inject_by_sqlSyntaxHighlighter(LSqlSyntaxHighlighter *syntaxHighlighter)
{
  _highlighter = syntaxHighlighter;
//  _highlighter->setParent(this);
}

void SqlEditorSupport::updateModels(DBObjectItem* item)
{
  _completerSupport->setItem(item);
  _helpLookupProvider->updateHelpModels(item->driverName());
  _highlighter->updateModels(item->driverName());
}

void SqlEditorSupport::setEditor(QPlainTextEdit *editor)
{
  _editor = editor;

  _helpTooltip = new LSimpleTooltip(_editor);
  _helpTooltip->setOpenExternalLinks(true);
  _helpTooltip->setLookupProvider(_helpLookupProvider);

  _keyInterceptor->attachToWidget(_editor);
  //Set editor object for key handlers
  foreach(AbstractKeySequenceHandler* handler, _keyInterceptor->handlers()) {
    if (handler->inherits(CLASS(QueryEditorKeyHandler))) {
      QueryEditorKeyHandler* editorKeyHandler = static_cast<QueryEditorKeyHandler*>(handler);
      editorKeyHandler->setEditor(_editor);
    }
  }

  _completerSupport->setWidget(_editor);
  _helpTooltip->setWidget(_editor);
  _highlighter->setDocument(_editor->document());
}

QString SqlEditorSupport::currentWord()
{
  QTextCursor cursor = _editor->textCursor();
  cursor.movePosition(QTextCursor::StartOfWord);
  cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);
  return cursor.selectedText();
}

QString SqlEditorSupport::previousWord()
{
  QTextCursor cursor = _editor->textCursor();
  cursor.movePosition(QTextCursor::PreviousWord);
  cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);
  return cursor.selectedText();
}

QPoint SqlEditorSupport::cursorGlobalPos()
{
  return _editor->mapToGlobal(_editor->cursorRect().bottomRight());
}

LDBObjectTableModel* SqlEditorSupport::objects()
{
  return _completerSupport->objectsModel();
}

void SqlEditorSupport::onHelpKey()
{
  _helpTooltip->popup(currentWord(), cursorGlobalPos());
}

void SqlEditorSupport::injectExtension(ExtensionPoint ep, QObject *e)
{
  qDebug() << "Inject QueryEditor extension:" << e->objectName();
  if (e->inherits(CLASS(AbstractKeySequenceHandler))) {
    if (ep.name() == EP_QUERYEDITOR_KEYSEQUENCE) {
      AbstractKeySequenceHandler* keyHander = static_cast<AbstractKeySequenceHandler*>(e);
      _keyInterceptor->registerHandler(keyHander);
    }
  }
}

QSet<KeySequence> HelpKeyHandler::keySequences()
{
  QSet<KeySequence> sequences;
  sequences << KeySequence(static_cast<QKeySequence>(Qt::CTRL | Qt::Key_Q));
  return sequences;
}
