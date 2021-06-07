#ifndef POSTGRESDATABASE_H
#define POSTGRESDATABASE_H

#include "sdk/objects/dbdatabaseitem.h"

class PostgresDatabase : public DBDatabaseItem
{
  Q_OBJECT
public:
  Q_INVOKABLE PostgresDatabase();
  ~PostgresDatabase();

  // DBDatabaseItem interface
protected:
  virtual QString getViewListSql() const Q_DECL_OVERRIDE;
  virtual QString getSequenceListSql() const Q_DECL_OVERRIDE;
  virtual QString getTriggerListSql() const Q_DECL_OVERRIDE;
  virtual QString getProcedureListSql() const Q_DECL_OVERRIDE;

  // DBDatabaseItem interface
public:
  virtual QString getAllObjectListSql() const Q_DECL_OVERRIDE;
};

#endif // POSTGRESDATABASE_H
