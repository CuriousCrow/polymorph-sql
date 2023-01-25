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
  virtual void reloadConstraintsModel() Q_DECL_OVERRIDE;
protected:
  QString createTableQuery(QString table) const;
  QString columnDef(const SqlColumn &col) const;
  QString typeDef(const SqlColumn &col) const;

  // DBObjectItem interface
public:
  virtual ActionResult insertMe() override;
  virtual ActionResult updateMe() override;
  virtual QString toDDL() const override;

};

#endif // FIREBIRDTABLE_H
