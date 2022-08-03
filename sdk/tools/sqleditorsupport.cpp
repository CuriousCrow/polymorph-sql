#include "sqleditorsupport.h"
#include "tools/keysequenceinterceptor.h"

SqlEditorSupport::SqlEditorSupport() : QObject()
{
  _keyInterceptor = new LKeySequenceInterceptor(this);
}

void SqlEditorSupport::inject_sqlCompleterSupport_into_form(SimpleSqlCompleterSupport *completerSupport)
{
  _completerSupport = completerSupport;
  _completerSupport->setParent(this);
}

void SqlEditorSupport::inject_helpLookupProvider(SqlHelpLookupProvider *lookupProvider)
{
  _helpLookupProvider = lookupProvider;
  _helpLookupProvider->setParent(this);
}

void SqlEditorSupport::inject_by_sqlSyntaxHighlighter(LSqlSyntaxHighlighter *syntaxHighlighter)
{
  _highlighter = syntaxHighlighter;
  _highlighter->setParent(this);
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

  _keyInterceptor->applyToWidget(_editor);
  _keyInterceptor->setKeySequence(QKeySequence(Qt::CTRL, Qt::Key_Q));
  connect(_keyInterceptor, SIGNAL(keySequencePressed(QKeySequence)),
          this, SLOT(onHelpKey()));

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

void SqlEditorSupport::onHelpKey()
{
  _helpTooltip->popup(currentWord(),
                      cursorGlobalPos());
}
