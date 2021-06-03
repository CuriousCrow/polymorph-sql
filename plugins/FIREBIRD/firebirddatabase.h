#ifndef FIREBIRDDATABASE_H
#define FIREBIRDDATABASE_H

#include <QObject>
#include "../../sdk/objects/dbdatabaseitem.h"

class FirebirdDatabase : public DBDatabaseItem
{
  Q_OBJECT
public:
  FirebirdDatabase(QString caption);
  virtual QString getAllObjectListSql() const Q_DECL_OVERRIDE;
};

#endif // FIREBIRDDATABASE_H
