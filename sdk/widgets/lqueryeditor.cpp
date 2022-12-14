#include "lqueryeditor.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMimeData>
#include <QDebug>
#include "utils/fileutils.h"


LQueryEditor::LQueryEditor(QWidget *parent) : QPlainTextEdit(parent)
{
}

QString LQueryEditor::currentWord()
{
  QTextCursor cursor = this->textCursor();
  cursor.movePosition(QTextCursor::StartOfWord);
  cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);
  return cursor.selectedText();
}

QString LQueryEditor::previousWord()
{
  QTextCursor cursor = this->textCursor();
  cursor.movePosition(QTextCursor::PreviousWord);
  cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);
  return cursor.selectedText();
}

QPoint LQueryEditor::cursorGlobalPos()
{
  return this->mapToGlobal(this->cursorRect().bottomRight());
}

void LQueryEditor::mousePressEvent(QMouseEvent *event)
{
  QPlainTextEdit::mousePressEvent(event);

  if (event->button() == Qt::LeftButton)
      emit wordClicked(currentWord(), event->modifiers());
}

void LQueryEditor::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        QUrl url = event->mimeData()->urls().first();
        if (url.isLocalFile() && (url.path().endsWith(".sql") || url.path().endsWith(".txt"))) {
            QString path = url.toLocalFile();
            qInfo() << "SqlEditor: Loading dropped file" << path;
            setPlainText(FileUtils::fileToString(path, true));
        }
        else {
            emit infoMessage(tr("Trying to drop unsupported file type"));
        }
    }
    else if (event->mimeData()->hasText()) {
        setPlainText(event->mimeData()->text());
    }
    else {
        emit infoMessage(tr("Trying to drop unsupported mime type"));
    }
}

LKeySequenceInterceptor::LKeySequenceInterceptor(QObject *parent) : QObject(parent)
{

}

void LKeySequenceInterceptor::setKeySequence(QKeySequence keySequence)
{
  _keySequence = keySequence;
}

void LKeySequenceInterceptor::applyToWidget(QWidget *widget)
{
  widget->installEventFilter(this);
}

bool LKeySequenceInterceptor::eventFilter(QObject *watched, QEvent *event)
{
  Q_UNUSED(watched)

  if (event->type() == QEvent::KeyPress) {
    QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
    int key = keyEvent->key();
    if (_keySequence.matches(QKeySequence(keyEvent->modifiers(), key))) {
      emit keySequencePressed(_keySequence);
    }
  }
  return false;
}

LMousePressedInterceptor::LMousePressedInterceptor(QObject *parent) : QObject(parent)
{
}

bool LMousePressedInterceptor::eventFilter(QObject *watched, QEvent *event)
{
  Q_UNUSED(watched)
  qDebug() << "Event filter:" << event;
  if (event->type() == QEvent::MouseButtonPress) {
    qDebug() << "Mouse press event" << static_cast<QMouseEvent*>(event);
  }
  return false;
}
