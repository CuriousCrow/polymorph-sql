#include "unisqltablemodelaction.h"

UniSqlTableModelAction::UniSqlTableModelAction() : QAction()
{

}

void UniSqlTableModelAction::setModel(UniSqlTableModel *model)
{
  _model = model;
}
