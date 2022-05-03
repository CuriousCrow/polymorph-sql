#ifndef DROPITEMOBJECTACTION_H
#define DROPITEMOBJECTACTION_H

#include <QObject>
#include "core/basecontextaction.h"

class DropItemObjectAction : public BaseItemPopupAction
{
    Q_OBJECT
public:
    Q_INVOKABLE DropItemObjectAction();

    // BaseContextAction interface
public slots:
    virtual void doAction() override;
};

#endif // DROPITEMOBJECTACTION_H
