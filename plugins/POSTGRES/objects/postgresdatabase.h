#ifndef POSTGRESDATABASE_H
#define POSTGRESDATABASE_H

#include "objects/dbdatabase.h"

/** PostgreSQL database item */
class PostgresDatabase : public DBDatabaseItem
{
  Q_OBJECT
public:
  Q_INVOKABLE PostgresDatabase();
  ~PostgresDatabase();

  // DBDatabaseItem interface
protected:

  // DBDatabaseItem interface
public:
  virtual QString getAllObjectListSql() const Q_DECL_OVERRIDE;
};

#endif // POSTGRESDATABASE_H
