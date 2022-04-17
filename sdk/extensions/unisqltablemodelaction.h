#ifndef UNISQLTABLEMODELACTION_H
#define UNISQLTABLEMODELACTION_H

#include <QAction>
#include <QObject>
#include "models/unisqltablemodel.h"

class UniSqlTableModelAction : public QAction
{
  Q_OBJECT
public:
  Q_INVOKABLE UniSqlTableModelAction();
  void setModel(UniSqlTableModel* model);
protected:
  UniSqlTableModel* _model;
};

#endif // UNISQLTABLEMODELACTION_H
