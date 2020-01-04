#ifndef FIREBIRDDATABASE_H
#define FIREBIRDDATABASE_H

#include <QObject>
#include "../dbdatabaseitem.h"

class FirebirdDatabase : public DBDatabaseItem
{
  Q_OBJECT
public:
  FirebirdDatabase(QString caption);
};

#endif // FIREBIRDDATABASE_H
