#ifndef MYSQLPLUGIN_H
#define MYSQLPLUGIN_H

#include <QObject>
#include "sdk/core/iocplugin.h"

class MysqlPlugin : public IocPlugin
{
  Q_OBJECT
public:
  MysqlPlugin(QObject *parent = nullptr);

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

#endif // MYSQLPLUGIN_H
