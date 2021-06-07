#include "core.h"

Core* Core::_singleton = nullptr;

Core::Core(QObject *parent) : QObject(parent)
{
  qDebug() << "Core object created";
}

Core *Core::instance(QObject *parent)
{
  if (!_singleton)
    _singleton = new Core(parent);
  return _singleton;
}

void Core::registerPlugin(IocPlugin *plugin)
{
  plugin->setParent(instance());
  instance()->_plugins.append(plugin);
}

IocPlugin *Core::plugin(QString driver, FeatureType featureType)
{
    qDebug() << "Get plugin for driver" << driver << "with feature" << featureType;
    Core* core = instance();
    foreach(IocPlugin* plugin, core->_plugins) {
        if (plugin->driverSupported(driver) && plugin->featureTypes().testFlag(featureType))
            return plugin;
    }
    return nullptr;
}

QStringList Core::pluginNames() const
{
    QStringList names;
    foreach(IocPlugin* plugin, _plugins) {
        names.append(plugin->title());
    }
    return names;
}

QStringList Core::supportedDrivers() const
{
    QStringList drivers;
    foreach(IocPlugin* plugin, _plugins) {
        if (!plugin->driver().isEmpty())
            drivers.append(plugin->driver());
    }
    return drivers;
}
