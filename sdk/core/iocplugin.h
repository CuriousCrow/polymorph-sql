#ifndef IOCPLUGIN_H
#define IOCPLUGIN_H

#include "dependencycontainer.h"
#include <QObject>
#include "../objects/dbobjectitem.h"
#include "sdk/abstractpluginmanager.h"

class IocPlugin : public DependencyContainer, public AbstractPlugin
{
    Q_OBJECT
public:
    IocPlugin(QObject *parent = nullptr);

    virtual QList<DBObjectItem::ItemType> supportedTypes() = 0;
};

#endif // IOCPLUGIN_H
