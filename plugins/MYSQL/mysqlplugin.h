#ifndef MYSQLPLUGIN_H
#define MYSQLPLUGIN_H

#include <QObject>
#include "core/iocplugin.h"

/** Plugin for MySQL database support */
class MysqlPlugin : public IocPlugin
{
    Q_OBJECT
//Enable metadata only plugin lib compilation
#ifndef SINGLEAPP
    Q_PLUGIN_METADATA(IID IocPlugin_iid FILE "MysqlPlugin.json")
    Q_INTERFACES(IocPlugin)
#endif
public:
  MysqlPlugin(QObject *parent = nullptr);

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

#endif // MYSQLPLUGIN_H
