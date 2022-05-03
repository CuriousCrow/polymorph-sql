#include "unisqltablefilteraction.h"
#include <QDebug>

UniSqlTableFilterAction::UniSqlTableFilterAction() : QAction()
{
}

void UniSqlTableFilterAction::setView(QListView *view)
{
  _listView = view;
  _filterModel = qobject_cast<SqlFilterManager*>(_listView->model());
}
