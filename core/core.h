#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QList>
#include "../sdk/core/iocplugin.h"

class Core : public QObject
{
  Q_OBJECT
public:
  static Core* instance(QObject* parent = nullptr);
  static void registerPlugin(IocPlugin* plugin);
  static IocPlugin* plugin(QString driver, FeatureType featureType);
  QStringList pluginNames() const;
  QStringList supportedDrivers() const;
signals:

public slots:

private:
  explicit Core(QObject *parent = nullptr);
  QList<IocPlugin*> _plugins;
  QHash<QString, IocPlugin*> _modules;
  static Core* _singleton;
};

#endif // CORE_H
