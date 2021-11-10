#ifndef TESTCLASSES_H
#define TESTCLASSES_H

#include <QObject>
#include "core/extensions.h"
#include "core/basecontextaction.h"

class TestExtension : public QObject, public AbstractExtension
{
  Q_OBJECT
public:
  TestExtension();

  // AbstractExtension interface
public:
  virtual bool supportsExtensionPoint(const ExtensionPoint &extensionPoint) const override;
};

class TestPopupAction : public BaseItemPopupAction
{
  Q_OBJECT
public:
    Q_INVOKABLE TestPopupAction();
    INJECT(Core*, core)

    // BaseContextAction interface
public slots:
    virtual void doAction() override;

    // AbstractContextAction interface
protected slots:
    virtual void updateState() override;
};

#endif // TESTCLASSES_H
