#include "testclasses.h"
#include <QDebug>
#include "core/extensionpoints.h"


TestExtension::TestExtension() : QObject(Q_NULLPTR)
{
  qDebug() << "TestExtension created";
}


bool TestExtension::supportsExtensionPoint(const ExtensionPoint &extensionPoint) const
{
  return extensionPoint.name() == EP_TEST_EXTENSION_POINT;
}

TestPopupAction::TestPopupAction()
{
  setText("Test action");
  _supportedTypes.insert(DBObjectItem::Table);
  _supportedTypes.insert(DBObjectItem::View);
  _supportedTypes.insert(DBObjectItem::Procedure);
  _supportedTypes.insert(DBObjectItem::Trigger);
  _supportedTypes.insert(DBObjectItem::Sequence);
}

void TestPopupAction::doAction()
{
  qDebug() << "Do the test action";
}

void TestPopupAction::updateState()
{
  BaseItemPopupAction::updateState();
}
