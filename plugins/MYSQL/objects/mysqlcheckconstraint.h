#ifndef MYSQLCHECKCONSTRAINT_H
#define MYSQLCHECKCONSTRAINT_H

#include "objects/dbcheckconstraint.h"
#include <QObject>

class MysqlCheckConstraint : public DBCheckConstraint
{
  Q_OBJECT
public:
  Q_INVOKABLE MysqlCheckConstraint();

  // DBObjectItem interface
public:
  virtual bool refresh() override;
};

#endif // MYSQLCHECKCONSTRAINT_H
