#include "lqueryeditor.h"
#include <QKeyEvent>


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

QPoint LQueryEditor::cursorGlobalPos()
{
    return this->mapToGlobal(this->cursorRect().bottomRight());
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
