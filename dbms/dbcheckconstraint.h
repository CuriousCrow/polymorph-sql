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
  virtual int type() const Q_DECL_OVERRIDE;
  virtual ActionResult insertMe() Q_DECL_OVERRIDE;

  // DBObjectItem interface
public:
  virtual bool refresh() Q_DECL_OVERRIDE;
};

#endif // DBCHECKCONSTRAINT_H
