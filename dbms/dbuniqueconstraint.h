#ifndef DBUNIQUECONSTRAINT_H
#define DBUNIQUECONSTRAINT_H

#include <QObject>
#include "dbconstraintitem.h"

class DBUniqueConstraint : public DBConstraintItem
{
  Q_OBJECT
public:
  DBUniqueConstraint(QString caption, QObject* parent = nullptr);

  // DBObjectItem interface
public:
  virtual int type() override;
  virtual ActionResult insertMe() override;
  virtual bool refresh() override;
};

#endif // DBUNIQUECONSTRAINT_H
