#ifndef POSTGRESCHECKCONSTRAINT_H
#define POSTGRESCHECKCONSTRAINT_H

#include <QObject>
#include "sdk/objects/dbcheckconstraint.h"

class PostgresCheckConstraint : public DBCheckConstraint
{
  Q_OBJECT
public:
  PostgresCheckConstraint(QString caption, QObject* parent = nullptr);

  // DBObjectItem interface
public:
  virtual bool refresh() Q_DECL_OVERRIDE;
};

#endif // POSTGRESCHECKCONSTRAINT_H
