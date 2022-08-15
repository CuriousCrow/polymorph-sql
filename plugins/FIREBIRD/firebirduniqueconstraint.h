#ifndef FIREBIRDUNIQUECONSTRAINT_H
#define FIREBIRDUNIQUECONSTRAINT_H

#include "objects/dbuniqueconstraint.h"
#include <QObject>

class FirebirdUniqueConstraint : public DBUniqueConstraint
{
  Q_OBJECT
public:
  Q_INVOKABLE FirebirdUniqueConstraint();

  // DBObjectItem interface
public:
  virtual bool refresh() override;
};

#endif // FIREBIRDUNIQUECONSTRAINT_H
