#include "queryeditorkeysequences.h"
#include <QDebug>

QETestHandler::QETestHandler()
{
}

bool QETestHandler::supportsExtensionPoint(const ExtensionPoint &extensionPoint) const
{
  return extensionPoint.name() == EP_QUERYEDITOR_KEYSEQUENCE;
}

QSet<KeySequence> QETestHandler::keySequences()
{
  QSet<KeySequence> sequences;
  sequences << KeySequence(Qt::CTRL + Qt::Key_G);
  return sequences;
}

bool QETestHandler::handle(const KeySequence &keySequence)
{
  Q_UNUSED(keySequence)
  qDebug() << "Hello from Test key sequence handler!";
  return true;
}


ToggleQueryCommentsHandler::ToggleQueryCommentsHandler() : QueryEditorKeyHandler()
{
}

bool ToggleQueryCommentsHandler::supportsExtensionPoint(const ExtensionPoint &extensionPoint) const
{
  return extensionPoint.name() == EP_QUERYEDITOR_KEYSEQUENCE;
}

QSet<KeySequence> ToggleQueryCommentsHandler::keySequences()
{
  QSet<KeySequence> sequences;
  sequences << KeySequence(Qt::CTRL + Qt::Key_Slash);
  return sequences;
}

bool ToggleQueryCommentsHandler::handle(const KeySequence &keySequence)
{
  Q_UNUSED(keySequence)
  qDebug() << "Toggle comments!" << _editor->toPlainText();
  QTextCursor cursor = _editor->textCursor();
  cursor.movePosition(QTextCursor::StartOfLine);
  cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
  bool commented = cursor.selectedText().startsWith("-- ");
  cursor.movePosition(QTextCursor::StartOfLine);
  if (commented) {
    cursor.deleteChar();
    cursor.deleteChar();
    cursor.deleteChar();
  } else {
    cursor.insertText("-- ");
  }

  _editor->setTextCursor(cursor);
  return false;
}

void QueryEditorKeyHandler::setEditor(LQueryEditor *editor)
{
  _editor = editor;
}
