#ifndef FIREBIRDPLUGIN_H
#define FIREBIRDPLUGIN_H

#include <QObject>
#include "objects/dbmsplugin.h"
#include "core/iocplugin.h"

/** Plugin for Firebird database support */
class FirebirdPlugin : public IocPlugin
{
    Q_OBJECT
//Enable metadata only plugin lib compilation
#ifndef SINGLEAPP
    Q_PLUGIN_METADATA(IID IocPlugin_iid FILE "FirebirdPlugin.json")
    Q_INTERFACES(IocPlugin)
#endif
public:
  Q_INVOKABLE FirebirdPlugin(QObject *parent = nullptr);
  // DbmsPlugin interface
public:
  virtual QList<DBObjectItem::ItemType> supportedTypes() override;
  virtual bool registerPlugin(DependencyContainer *c) override;

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
