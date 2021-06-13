#ifndef POSTGRESPLUGIN_H
#define POSTGRESPLUGIN_H

#include <QObject>
#include "sdk/core/iocplugin.h"

class PostgresPlugin : public IocPlugin
{
  Q_OBJECT
public:
  PostgresPlugin(QObject *parent = nullptr);

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

#endif // POSTGRESPLUGIN_H
