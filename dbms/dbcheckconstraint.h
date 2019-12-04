#ifndef DBCHECKCONSTRAINT_H
#define DBCHECKCONSTRAINT_H

#include <QObject>
#include "dbconstraintitem.h"

class DBCheckConstraint : public DBConstraintItem
{
  Q_OBJECT
public:
  DBCheckConstraint(QString caption, QObject* parent = nullptr);

  // DBObjectItem interface
public:
  virtual int type() override;
  virtual ActionResult insertMe() override;

  // DBObjectItem interface
public:
  virtual bool refresh() override;
};

#endif // DBCHECKCONSTRAINT_H
