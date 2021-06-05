#include "basepluginmanager.h"
#include <QDebug>
#include "sdk/objects/appconst.h"

BasePluginManager* BasePluginManager::_singleton = nullptr;

BasePluginManager::BasePluginManager(QObject* parent) : QObject(parent)
{
    qDebug() << "Plugin manager created";
}

DbmsPlugin *BasePluginManager::getPlugin(QString driver)
{
    qDebug() << "Plugin" << driver << "found:" << _plugins.contains(driver);
    return _plugins.value(driver);
}

void BasePluginManager::registerPlugin(DbmsPlugin *plugin)
{
    _plugins.insert(plugin->driver(), plugin);
}

BasePluginManager *BasePluginManager::instance(QObject *parent)
{
    if (!_singleton)
        _singleton = new BasePluginManager(parent);
    return _singleton;
}

DBObjectItem *BasePluginManager::newDbmsObject(QString driverName, DBObjectItem::ItemType type, QString caption, QObject *parent)
{
    DbmsPlugin* dbms = getPlugin(driverName);
    switch (type) {
    case DBObjectItem::Database:
        return dbms->newDatabaseItem(caption, parent);
    case DBObjectItem::Table:
        return dbms->newTableItem(caption, parent);
    case DBObjectItem::View:
        return dbms->newViewItem(caption, parent);
    case DBObjectItem::Procedure:
        return dbms->newProcedureItem(caption, parent);
    case DBObjectItem::Trigger:
        return dbms->newTriggerItem(caption, parent);
    case DBObjectItem::Sequence:
        return dbms->newSequenceItem(caption, parent);
    case DBObjectItem::Folder:
        return dbms->newFolderItem(parent);
    default:
        qWarning() << "Cannot instantiate object of type:" << type;
        return nullptr;
    }
}

AbstractDatabaseEditForm *BasePluginManager::getObjectEditForm(QString driverName, DBObjectItem::ItemType type)
{
    DbmsPlugin* dbms = getPlugin(driverName);
    return dbms->formByType(type);
}
