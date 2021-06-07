#ifndef BASEPLUGINMANAGER_H
#define BASEPLUGINMANAGER_H

#include "sdk/abstractpluginmanager.h"
#include <QObject>
#include <QHash>
#include "sdk/objects/dbmsplugin.h"

class BasePluginManager : public QObject
{    
    Q_OBJECT
private:
    BasePluginManager(QObject* parent = nullptr);
    DbmsPlugin* getPlugin(QString driver);
    static BasePluginManager* _singleton;
    QHash<QString, DbmsPlugin*> _plugins;
public:
    void registerPlugin(DbmsPlugin* plugin);
    static BasePluginManager* instance(QObject* parent = nullptr);

    // AbstractPluginManager interface
public:
//    virtual DBObjectItem *newDbmsObject(QString driverName, DBObjectItem::ItemType type, QString caption, QObject *parent = nullptr) override;
    virtual AbstractDatabaseEditForm *getObjectEditForm(QString driverName, DBObjectItem::ItemType type);
};

#endif // BASEPLUGINMANAGER_H
