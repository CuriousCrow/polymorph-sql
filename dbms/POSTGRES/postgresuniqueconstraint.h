#ifndef POSTGRESUNIQUECONSTRAINT_H
#define POSTGRESUNIQUECONSTRAINT_H

#include <QObject>
#include "../dbuniqueconstraint.h"

class PostgresUniqueConstraint : public DBUniqueConstraint
{
  Q_OBJECT
public:
  PostgresUniqueConstraint(QString caption, QObject* parent = nullptr);
};

#endif // POSTGRESUNIQUECONSTRAINT_H
