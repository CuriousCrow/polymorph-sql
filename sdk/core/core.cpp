#include "core.h"
#include <QDebug>
#include "extensions.h"

#define COREBEAN "core"

Core* Core::_singleton = nullptr;

Core::Core(QObject *parent) : DependencyContainer(parent)
{
    qDebug() << "Core object created";
}

Core::~Core()
{
    removeSingleton(COREBEAN);
}

Core *Core::instance(QObject *parent)
{
  if (!_singleton) {
    _singleton = new Core(parent);
    DependencyMeta* meta = new DependencyMeta(COREBEAN, CLASSMETA(Core), InstanceMode::Singleton);
    _singleton->registerSingletonObject(meta, _singleton);
  }
  return _singleton;
}

void Core::registerPlugin(IocPlugin *plugin)
{
  qDebug() << "Register plugin:" << plugin->title();
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
    p.insert(F_DRIVER_NAME, DRIVER_BASE);
    return dependency<AbstractDatabaseEditForm>(p);
}

DBObjectItem *Core::newObjInstance(const QString &driver, DBObjectItem::ItemType itemType)
{
    QString className = DBObjectItem::baseClassByType(itemType);
    qDebug() << "New object instance" << driver << className;
    QVariantHash p;
    p.insert(F_DRIVER_NAME, driver);
    p.insert(F_TYPE, itemType);
    DBObjectItem* itemObj = static_cast<DBObjectItem*>(dependency(className, p));
    if (itemObj)
        return itemObj;
    p.remove(F_DRIVER_NAME);
    return static_cast<DBObjectItem*>(dependency(className, p));
}


void Core::newInstanceProccessing(QObject *obj)
{
  //Extension injection for Extensible dependencies
  if (obj->inherits(EXTENSIBLE_CLASS)) {
    qDebug() << "Extensible object detected:" << obj->objectName();
    Extensible* extensibleObj = dynamic_cast<Extensible*>(obj);
    QSet<ExtensionPoint> extPoints = extensibleObj->extensionPoints();
    foreach(ExtensionPoint extPoint, extPoints) {
      qDebug() << "Search extension for extension point:" << extPoint.name();
      QStringList extensionNames = namesByClass(extPoint.extensionClass());
      foreach(QString name, extensionNames) {
        QObject* plainObj = dependency(name);
        if (plainObj->inherits(EXTENSION_CLASS)) {
          AbstractExtension* extensionObj = dynamic_cast<AbstractExtension*>(plainObj);
          if (extensionObj && extensionObj->supportsExtensionPoint(extPoint)) {
            extensibleObj->injectExtension(extPoint, plainObj);
          }
        }
        else {
          qWarning() << plainObj->objectName() << "does not implement AbstractExtension";
        }

      }
    }
  }
}
