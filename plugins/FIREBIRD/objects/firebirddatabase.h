#ifndef FIREBIRDDATABASE_H
#define FIREBIRDDATABASE_H

#include <QObject>
#include "objects/dbdatabaseitem.h"

class FirebirdDatabase : public DBDatabaseItem
{
  Q_OBJECT
public:
  Q_INVOKABLE FirebirdDatabase();
  virtual QString getAllObjectListSql() const Q_DECL_OVERRIDE;
};

#endif // FIREBIRDDATABASE_H
