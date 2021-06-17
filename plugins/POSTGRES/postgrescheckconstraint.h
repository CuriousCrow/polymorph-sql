#ifndef POSTGRESCHECKCONSTRAINT_H
#define POSTGRESCHECKCONSTRAINT_H

#include <QObject>
#include "objects/dbcheckconstraint.h"

class PostgresCheckConstraint : public DBCheckConstraint
{
  Q_OBJECT
public:
  Q_INVOKABLE PostgresCheckConstraint();

  // DBObjectItem interface
public:
  virtual bool refresh() Q_DECL_OVERRIDE;
};

#endif // POSTGRESCHECKCONSTRAINT_H
