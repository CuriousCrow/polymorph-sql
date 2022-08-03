#include "keysequenceinterceptor.h"

#include <QKeyEvent>
#include <QWidget>
#include <QDebug>

KeySequenceInterceptor::KeySequenceInterceptor(QObject *parent) : QObject(parent)
{

}

void KeySequenceInterceptor::attachToWidget(QWidget *widget)
{
    widget->installEventFilter(this);
}

void KeySequenceInterceptor::registerHandler(KeySequence keySequence, AbstractKeySequenceHandler *keyHandler)
{
    keyHandler->setParent(this);
    qDebug() << "registerHandler:" << keySequence;
    _handlerHash.insert(keySequence, keyHandler);
}

void KeySequenceInterceptor::registerHandler(AbstractKeySequenceHandler *keyHandler)
{
  foreach(KeySequence sequence, keyHandler->keySequences()) {
    registerHandler(sequence, keyHandler);
  }
}

QList<AbstractKeySequenceHandler *> KeySequenceInterceptor::handlers() const
{
  return _handlerHash.values();
}

bool KeySequenceInterceptor::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched)
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        int key = keyEvent->key();
        KeySequence eventSequence(key + keyEvent->modifiers());
        qDebug() << "KeySequenceInterceptor:" << eventSequence;
        AbstractKeySequenceHandler* hander = _handlerHash.value(eventSequence);
        if (hander) {
            return hander->handle(eventSequence);
        }
    }
    return false;
}

AbstractKeySequenceHandler::AbstractKeySequenceHandler() : QObject()
{

}

AbstractKeySequenceHandler::~AbstractKeySequenceHandler()
{
}

KeySequence::KeySequence(const QString &key, QKeySequence::SequenceFormat format) : QKeySequence(key, format)
{
}

KeySequence::KeySequence(int k1, int k2, int k3, int k4) : QKeySequence(k1, k2, k3, k4)
{
}

KeySequence::KeySequence(const QKeySequence &ks) : QKeySequence(ks)
{
}

KeySequence::KeySequence(QKeySequence::StandardKey key) : QKeySequence(key)
{
}
