#ifndef POSTGRESFUNCTION_H
#define POSTGRESFUNCTION_H

#include <QObject>
#include "objects/dbprocedure.h"

/** PostgreSQL function item */
class PostgresFunctionItem : public DBProcedureItem
{
  Q_OBJECT
public:
  Q_INVOKABLE PostgresFunctionItem();

  // DBObjectItem interface
public:
  virtual bool refresh() Q_DECL_OVERRIDE;
  virtual ActionResult insertMe() Q_DECL_OVERRIDE;
  virtual ActionResult updateMe() Q_DECL_OVERRIDE;
  virtual ActionResult deleteMe() Q_DECL_OVERRIDE;
  virtual QString toDDL() const Q_DECL_OVERRIDE;
};

#endif // POSTGRESFUNCTION_H
