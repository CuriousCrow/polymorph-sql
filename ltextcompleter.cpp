#include "ltextcompleter.h"

#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QAbstractItemView>


LTextCompleter::LTextCompleter(QObject *parent): QCompleter(parent)
{
}

LTextCompleter::LTextCompleter(QAbstractItemModel *model, QObject *parent):
  QCompleter(model, parent)
{
}

LTextCompleter::LTextCompleter(const QStringList &completions, QObject *parent):
  QCompleter(completions, parent)
{
}

LTextCompleter::~LTextCompleter()
{
}

bool LTextCompleter::eventFilter(QObject *o, QEvent *e)
{
  if ((e->type() == QEvent::KeyPress) && isMultilineEditor()){
    QKeyEvent *ke = static_cast<QKeyEvent *>(e);
    switch (ke->key()) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
    case Qt::Key_Tab:
      if (popup()->isVisible()){
        popup()->hide();
        if (popup()->currentIndex().isValid()){
          QTextCursor cursor = textCursor();
          cursor.movePosition(QTextCursor::StartOfWord);
          cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
          cursor.removeSelectedText();
          cursor.insertText(popup()->currentIndex().data().toString());
          setTextCursor(cursor);
        }
        return true;
      }
    case Qt::Key_Space:
      if (ke->modifiers().testFlag(Qt::ControlModifier)){
        QTextCursor cursor = textCursor();
        cursor.movePosition(QTextCursor::StartOfWord);
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        if (cursor.selectedText().length() >= _minCompletionPrefixLength){
          setCompletionPrefix(cursor.selectedText());
          QRect rect = QRect(cursorRect().bottomLeft(), QSize(100, 5));
          complete(rect);
        }
        return true;
      }
    }
  }
  return QCompleter::eventFilter(o, e);
}
int LTextCompleter::minCompletionPrefixLength() const
{
  return _minCompletionPrefixLength;
}

void LTextCompleter::setMinCompletionPrefixLength(int minCompletionPrefixLength)
{
  _minCompletionPrefixLength = minCompletionPrefixLength;
}


bool LTextCompleter::isMultilineEditor()
{
  return widget()->inherits(QPlainTextEdit::staticMetaObject.className())
      || widget()->inherits(QTextEdit::staticMetaObject.className());
}

QTextCursor LTextCompleter::textCursor()
{
  if (widget()->inherits(QPlainTextEdit::staticMetaObject.className()))
    return ((QPlainTextEdit*)widget())->textCursor();
  else
    return ((QTextEdit*)widget())->textCursor();
}

QRect LTextCompleter::cursorRect()
{
  if (widget()->inherits(QPlainTextEdit::staticMetaObject.className()))
    return ((QPlainTextEdit*)widget())->cursorRect();
  else
    return ((QTextEdit*)widget())->cursorRect();
}

void LTextCompleter::setTextCursor(QTextCursor cursor)
{
  if (widget()->inherits(QPlainTextEdit::staticMetaObject.className()))
    return ((QPlainTextEdit*)widget())->setTextCursor(cursor);
  else
    return ((QTextEdit*)widget())->setTextCursor(cursor);
}
