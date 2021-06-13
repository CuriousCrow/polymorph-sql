#include "core.h"

Core* Core::_singleton = nullptr;

Core::Core(QObject *parent) : DependencyContainer(parent)
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
  Core* core = instance();
  plugin->registerPlugin(core);
  plugin->setParent(core);
  instance()->_plugins.append(plugin);
}

IocPlugin *Core::plugin(QString driver, FeatureType featureType)
{
    qDebug() << "Get plugin for driver" << driver << "with feature" << featureType;
    Core* core = instance();
    foreach(IocPlugin* plugin, core->_plugins) {
        if (plugin->driverSupported(driver) && plugin->featureTypes().testFlag(featureType)) {
            qDebug() << "Plugin match:" << plugin->title();
            return plugin;
        }
    }
    return plugin("", featureType);
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

QList<IocPlugin *> Core::plugins()
{
    return _plugins;
}

AbstractDatabaseEditForm *Core::objectForm(const QString &driver, DBObjectItem::ItemType itemType)
{
    QVariantHash p;
    p.insert(F_DRIVER_NAME, driver);
    p.insert(F_TYPE, itemType);
    AbstractDatabaseEditForm* form = dependency<AbstractDatabaseEditForm>(p);
    if (form)
        return form;
    p.remove(F_DRIVER_NAME);
    return dependency<AbstractDatabaseEditForm>(p);
}
