#include "abstractcontextaction.h"

AbstractContextAction::AbstractContextAction(QObject* parent) : QAction(parent)
{
    setText("Copy");
}

void AbstractContextAction::setContext(AbstractUserContext *context)
{
    _context = context;
    connect(_context, &AbstractUserContext::contextChanged, this, &AbstractContextAction::updateState);
}
