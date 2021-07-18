#ifndef IOCPLUGIN_H
#define IOCPLUGIN_H

#include "dependencycontainer.h"
#include <QObject>
#include "../objects/dbobjectitem.h"
#include "../abstractplugin.h"

class IocPlugin : public QObject, public AbstractPlugin
{
    Q_OBJECT
public:
    IocPlugin(QObject *parent = nullptr);

    virtual bool registerPlugin(DependencyContainer* container) = 0;

    virtual QList<DBObjectItem::ItemType> supportedTypes() = 0;
};

#define IocPlugin_iid "ru.levolex.iocplugin"
Q_DECLARE_INTERFACE(IocPlugin, IocPlugin_iid)


#endif // IOCPLUGIN_H
