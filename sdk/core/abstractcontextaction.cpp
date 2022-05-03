#include "abstractcontextaction.h"

AbstractContextAction::AbstractContextAction(QObject* parent) : QAction(parent)
{
    setText(tr("Copy"));
}

void AbstractContextAction::setContext(AbstractUserContext *context)
{
    _context = context;
    connect(_context, &AbstractUserContext::contextChanged, this, &AbstractContextAction::updateState);
}
