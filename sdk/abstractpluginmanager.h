#ifndef ABSTRACTPLUGINMANAGER_H
#define ABSTRACTPLUGINMANAGER_H

#include "../sdk/objects/dbobjectitem.h"
#include "../sdk/forms/abstractdatabaseitemform.h"

enum FeatureType {
    DbmsObjects,
    DbmsForms,
    FormActions
};

Q_DECLARE_FLAGS(FeatureTypes, FeatureType)

class AbstractPlugin {
public:
    virtual QString title() = 0;
    virtual QString author() = 0;
    virtual int majorVersion() = 0;
    virtual int minorVersion() = 0;
    virtual FeatureTypes featureTypes() = 0;
    virtual bool driverSupported(QString driverName) = 0;
};

class AbstractPluginManager {
public:
    virtual DBObjectItem* newDbmsObject(QString driverName, DBObjectItem::ItemType type, QString caption = "", QObject* parent = 0) = 0;
    virtual AbstractDatabaseEditForm* getObjectEditForm(QString driverName, DBObjectItem::ItemType type) = 0;
};


#endif // ABSTRACTPLUGINMANAGER_H
