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
