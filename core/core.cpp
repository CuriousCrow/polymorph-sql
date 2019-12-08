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

void Core::registerModule(DbmsPlugin *module)
{
  module->setParent(instance());
  instance()->_modules.insert(module->driver(), module);
}

DbmsPlugin *Core::module(QString name)
{
  qDebug() << "Get module:" << name << _singleton->_modules.keys();
  return _singleton->_modules.value(name);
}

QStringList Core::moduleNames()
{
  return _modules.keys();
}
