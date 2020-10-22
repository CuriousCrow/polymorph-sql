#ifndef MYSQLDATABASE_H
#define MYSQLDATABASE_H

#include "../dbdatabaseitem.h"

class MysqlDatabase : public DBDatabaseItem
{
  Q_OBJECT
public:
  MysqlDatabase(QString caption);
  ~MysqlDatabase();

  // DBObjectItem interface
public:
  virtual bool reloadChildren();
  virtual QString getAllObjectListSql();
};

#endif // MYSQLDATABASE_H
