#ifndef FIREBIRDTABLE_H
#define FIREBIRDTABLE_H

#include "objects/dbtableitem.h"
#include "core/dependencycontainer.h"
#include "models/sqlcolumnmodel.h"

class FirebirdTable : public DBTableItem
{
  Q_OBJECT
public:
  Q_INVOKABLE FirebirdTable();
  virtual ~FirebirdTable() override;

  INJECT_INITIALIZE(SqlColumnModel*, _columnsModel, baseColumnModel)

  // DBTableItem interface
public:
  virtual void reloadColumnsModel() Q_DECL_OVERRIDE;
};

#endif // FIREBIRDTABLE_H
