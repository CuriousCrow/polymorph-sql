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
  qDebug() << model->rowCount();
}

LTextCompleter::LTextCompleter(const QStringList &completions, QObject *parent):
  QCompleter(completions, parent)
{
}

LTextCompleter::~LTextCompleter()
{
}

bool LTextCompleter::tryToComplete(QString prefix, bool replaceIfOneOption)
{
  QTextCursor cursor = textCursor();
  cursor.movePosition(QTextCursor::StartOfWord);
  cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
  if (prefix.length() >= _minCompletionPrefixLength){
    setCompletionPrefix(prefix);
    //Если есть только один вариант, то сразу его подставляем
    if (replaceIfOneOption && completionCount() == 1) {
      cursor.removeSelectedText();
      QAbstractItemModel* popupModel = popup()->model();
      cursor.insertText(popupModel->data(popupModel->index(0, completionColumn())).toString());
      return true;
    }
    QRect rect = QRect(cursorRect().bottomLeft(), QSize(_popupWidth, 5));
    complete(rect);
    //Если вариантов несколько, выделяем первый
    if (completionCount() > 0) {
      QAbstractItemModel* popupModel = popup()->model();
      popup()->setCurrentIndex(popupModel->index(0, completionColumn()));
    }
  }
  return false;
}

QString LTextCompleter::getCompletionPrefix()
{
  QTextCursor cursor = textCursor();
  cursor.movePosition(QTextCursor::StartOfWord, QTextCursor::KeepAnchor);
  return cursor.selectedText();
}

QString LTextCompleter::getCompletionContext()
{
  QTextCursor cursor = textCursor();
  while(!cursor.atStart()) {
    cursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::KeepAnchor);
    if (cursor.selectedText().startsWith(" "))
      break;
  }
  return cursor.selectedText().trimmed();
}

bool LTextCompleter::eventFilter(QObject *o, QEvent *e)
{
  if ((e->type() == QEvent::KeyPress) && isMultilineEditor()){
    QKeyEvent *ke = static_cast<QKeyEvent *>(e);
    //    qDebug() << "Key pressed:" << ke->text();
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
      //TODO: Code should be checked
      return false;
    case Qt::Key_Space:
      if (ke->modifiers().testFlag(Qt::ControlModifier)){
        emit completerRequested(getCompletionContext());
        tryToComplete(getCompletionPrefix(), true);
        return true;
      }
      else {
        popup()->hide();
      }
    }
    if (ke->text().isSimpleText() && !ke->text().isEmpty()) {
      //      qDebug() << "Simple text:" << ke->text();
      QString prefix = getCompletionPrefix().append(ke->text());
      if (popup()->isVisible() && tryToComplete(prefix))
        return true;
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
    return (qobject_cast<QPlainTextEdit*>(widget()))->textCursor();
  else
    return (qobject_cast<QTextEdit*>(widget()))->textCursor();
}

QRect LTextCompleter::cursorRect()
{
  if (widget()->inherits(QPlainTextEdit::staticMetaObject.className()))
    return (qobject_cast<QPlainTextEdit*>(widget()))->cursorRect();
  else
    return (qobject_cast<QTextEdit*>(widget()))->cursorRect();
}

void LTextCompleter::setTextCursor(QTextCursor cursor)
{
  if (widget()->inherits(QPlainTextEdit::staticMetaObject.className()))
    return (qobject_cast<QPlainTextEdit*>(widget()))->setTextCursor(cursor);
  else
    return (qobject_cast<QTextEdit*>(widget()))->setTextCursor(cursor);
}


