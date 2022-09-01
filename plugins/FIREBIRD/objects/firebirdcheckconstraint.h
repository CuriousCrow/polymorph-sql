#ifndef FIREBIRDCHECKCONSTRAINT_H
#define FIREBIRDCHECKCONSTRAINT_H

#include "objects/dbcheckconstraint.h"
#include <QObject>

class FirebirdCheckConstraint : public DBCheckConstraint
{
  Q_OBJECT
public:
  Q_INVOKABLE FirebirdCheckConstraint();

  // DBObjectItem interface
public:
  virtual bool refresh() override;
};

#endif // FIREBIRDCHECKCONSTRAINT_H
