#ifndef ABSTRACTCONTEXTACTION_H
#define ABSTRACTCONTEXTACTION_H

#include <QAction>
#include <QObject>
#include "abstractusercontext.h"

#define P_FOCUS_WIDGET "focusedWidget"

class AbstractContextAction : public QAction
{
  Q_OBJECT
public:
    AbstractContextAction(QObject* parent = nullptr);
    void setContext(AbstractUserContext* context);
protected:
    AbstractUserContext* _context;
protected slots:
    virtual void updateState() = 0;
};

#endif // ABSTRACTCONTEXTACTION_H
