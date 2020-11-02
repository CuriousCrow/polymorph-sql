#ifndef MYSQLDATABASE_H
#define MYSQLDATABASE_H

#include "../dbdatabaseitem.h"

class MysqlDatabase : public DBDatabaseItem
{
  Q_OBJECT
public:
  MysqlDatabase(QString caption);
  ~MysqlDatabase() Q_DECL_OVERRIDE;

  // DBObjectItem interface
public:
  virtual bool reloadChildren() Q_DECL_OVERRIDE;
  virtual QString getAllObjectListSql() const Q_DECL_OVERRIDE;
};

#endif // MYSQLDATABASE_H
