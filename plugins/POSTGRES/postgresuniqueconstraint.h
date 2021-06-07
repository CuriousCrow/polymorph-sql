#ifndef POSTGRESUNIQUECONSTRAINT_H
#define POSTGRESUNIQUECONSTRAINT_H

#include <QObject>
#include "sdk/objects/dbuniqueconstraint.h"

class PostgresUniqueConstraint : public DBUniqueConstraint
{
  Q_OBJECT
public:
  Q_INVOKABLE PostgresUniqueConstraint();

  // DBObjectItem interface
public:
  virtual bool refresh() Q_DECL_OVERRIDE;
};

#endif // POSTGRESUNIQUECONSTRAINT_H
