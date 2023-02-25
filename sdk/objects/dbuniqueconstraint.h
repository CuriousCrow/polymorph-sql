#ifndef DBUNIQUECONSTRAINT_H
#define DBUNIQUECONSTRAINT_H

#include <QObject>
#include "dbconstraintitem.h"

class DBUniqueConstraint : public DBConstraintItem
{
  Q_OBJECT
public:
  Q_INVOKABLE DBUniqueConstraint(QString caption = "", QObject* parent = nullptr);

  // DBObjectItem interface
public:
  virtual int type() const Q_DECL_OVERRIDE;
  virtual ActionResult insertMe() Q_DECL_OVERRIDE;
  virtual bool refresh() Q_DECL_OVERRIDE;
  virtual QString toDDL() const Q_DECL_OVERRIDE;
};

#endif // DBUNIQUECONSTRAINT_H
