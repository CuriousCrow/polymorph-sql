#ifndef BASECONTEXTACTION_H
#define BASECONTEXTACTION_H

#include "abstractcontextaction.h"
#include <QObject>
#include <QSet>
#include "objects/dbobjectitem.h"
#include "baseusercontext.h"
#include "core/core.h"

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

class BaseItemPopupAction : public BaseContextAction
{
    Q_OBJECT
public:
    BaseItemPopupAction(QObject* parent = nullptr);
protected:
    QSet<DBObjectItem::ItemType> _supportedTypes;

    // AbstractContextAction interface
protected slots:
    virtual void updateState() override;
};

class MainMenuItem
{
public:
    virtual QStringList menuPath() = 0;
};



#endif // BASECONTEXTACTION_H

