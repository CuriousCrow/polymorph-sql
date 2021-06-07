#ifndef FIREBIRDPLUGIN_H
#define FIREBIRDPLUGIN_H

#include <QObject>
#include "sdk/objects/dbmsplugin.h"
#include "sdk/core/iocplugin.h"


class FirebirdPlugin : public IocPlugin
{
    Q_OBJECT
public:
  Q_INVOKABLE FirebirdPlugin(QObject *parent = nullptr);
  // DbmsPlugin interface
public:
  virtual QList<DBObjectItem::ItemType> supportedTypes() override;

  // AbstractPlugin interface
public:
  virtual QString title() override;
  virtual QString author() override;
  virtual int majorVersion() override;
  virtual int minorVersion() override;
  virtual FeatureTypes featureTypes() override;
  virtual bool driverSupported(QString driverName) override;
  virtual QString driver() override;
};

#endif // FIREBIRDPLUGIN_H
