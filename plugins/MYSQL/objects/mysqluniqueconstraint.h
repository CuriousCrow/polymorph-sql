#ifndef MYSQLUNIQUECONSTRAINT_H
#define MYSQLUNIQUECONSTRAINT_H

#include <QObject>
#include "objects/dbuniqueconstraint.h"

class MysqlUniqueConstraint : public DBUniqueConstraint
{
  Q_OBJECT
public:
  Q_INVOKABLE MysqlUniqueConstraint();

  // DBObjectItem interface
public:
  virtual bool refresh() override;
};

#endif // MYSQLUNIQUECONSTRAINT_H
