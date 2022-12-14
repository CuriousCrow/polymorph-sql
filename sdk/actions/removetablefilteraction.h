#ifndef REMOVETABLEFILTERACTION_H
#define REMOVETABLEFILTERACTION_H

#include <QAction>
#include <QObject>
#include "extensions/unisqltablefilteraction.h"
#include "core/extensions.h"

class RemoveTableFilterAction : public UniSqlTableFilterAction, public AbstractExtension
{
  Q_OBJECT
public:
  Q_INVOKABLE RemoveTableFilterAction();

  // AbstractExtension interface
public:
  virtual bool supportsExtensionPoint(const ExtensionPoint &extensionPoint) const override;

protected slots:
  virtual void doAction();
};

#endif // REMOVETABLEFILTERACTION_H
