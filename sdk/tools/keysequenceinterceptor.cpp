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

void KeySequenceInterceptor::registerHandler(QKeySequence keySequence, AbstractKeySequenceHandler *keyHandler)
{
    keyHandler->setParent(this);
    qDebug() << "registerHandler:" << keySequence;
    _handlerHash.insert(keySequence, keyHandler);
}

void KeySequenceInterceptor::registerHandler(AbstractKeySequenceHandler *keyHandler)
{
  foreach(QKeySequence sequence, keyHandler->keySequences()) {
    registerHandler(sequence, keyHandler);
  }
}

void KeySequenceInterceptor::registerHandler(QKeySequence keySequence, KeyHandlerFunc handlerFunc)
{
    registerHandler(keySequence, new KeySequenceHandlerWrapper(handlerFunc));
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

        QKeySequence eventSequence(keyEvent->keyCombination());
        // qDebug() << "KeySequenceInterceptor:" << eventSequence;
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

KeySequenceHandlerWrapper::KeySequenceHandlerWrapper(KeyHandlerFunc handerFunc) : AbstractKeySequenceHandler()
{
    _handlerFunc = handerFunc;
}

QSet<QKeySequence> KeySequenceHandlerWrapper::keySequences()
{
    QSet<QKeySequence> set;
    return set;
}

bool KeySequenceHandlerWrapper::handle(const QKeySequence &keySequence)
{
    _handlerFunc(keySequence);
    return true;
}
