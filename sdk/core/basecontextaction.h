#ifndef BASECONTEXTACTION_H
#define BASECONTEXTACTION_H

#include "abstractcontextaction.h"
#include <QObject>
#include <QSet>
#include "objects/dbobjectitem.h"
#include "baseusercontext.h"
#include "core/core.h"
#include "core/extensions.h"

#define I_MAINMENU_ITEM "MainMenuItem"

class BaseContextAction : public AbstractContextAction
{
    Q_OBJECT
public:
    BaseContextAction(QObject* parent = nullptr);
    Q_INVOKABLE void inject_by_context(BaseUserContext* context);
protected:
    BaseUserContext* context();
public slots:
    virtual void doAction();
};

class BaseItemPopupAction : public BaseContextAction, public AbstractExtension
{
    Q_OBJECT
public:
    BaseItemPopupAction(QObject* parent = nullptr);
protected:
    QSet<DBObjectItem::ItemType> _supportedTypes;

    // AbstractContextAction interface
protected slots:
    virtual void updateState() override;

    // AbstractExtension interface
public:
    virtual bool supportsExtensionPoint(const ExtensionPoint &extensionPoint) const override;
};

class MainMenuItem
{
public:
    virtual QStringList menuPath() = 0;
};



#endif // BASECONTEXTACTION_H

