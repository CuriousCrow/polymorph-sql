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

GenerateTableAliasHandler::GenerateTableAliasHandler() : QueryEditorKeyHandler()
{
}

QSet<KeySequence> GenerateTableAliasHandler::keySequences()
{
  QSet<KeySequence> sequences;
  sequences << KeySequence(Qt::CTRL + Qt::Key_T);
  return sequences;
}

QString GenerateTableAliasHandler::generateAlias(QString tableName)
{
//  qDebug() << "Table name: " << tableName;
  QStringList sl = tableName.split("_", Qt::SkipEmptyParts);
  QString alias;
  foreach(QString word, sl) {
    alias += word.at(0).toLower();
  }
  return alias;
}

bool GenerateTableAliasHandler::handle(const KeySequence &keySequence)
{
  Q_UNUSED(keySequence)

  QString curWord = _editor->currentWord();
  QString prevWord = _editor->previousWord();

  QString tableAlias = generateAlias(curWord.isEmpty() ? prevWord : curWord);
  if (!curWord.isEmpty()) {
    QTextCursor cursor = _editor->textCursor();
    cursor.movePosition(QTextCursor::EndOfWord);
    cursor.insertText(" ");
    _editor->setTextCursor(cursor);
  }
  _editor->textCursor().insertText(tableAlias);
  return false;
}

bool GenerateTableAliasHandler::supportsExtensionPoint(const ExtensionPoint &extensionPoint) const
{
  return extensionPoint.name() == EP_QUERYEDITOR_KEYSEQUENCE;
}
