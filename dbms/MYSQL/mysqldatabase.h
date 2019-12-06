#ifndef MYSQLDATABASE_H
#define MYSQLDATABASE_H

#include "../dbdatabaseitem.h"

class MysqlDatabase : public DBDatabaseItem
{
  Q_OBJECT
public:
  MysqlDatabase(QString caption);
  ~MysqlDatabase();

  virtual DBTableItem* createNewTableItem(QString caption, QObject* parent = nullptr);
  // DBObjectItem interface
public:
  virtual bool reloadChildren();

  // DBDatabaseItem interface
protected:
  virtual QString getViewListSql();
  virtual QString getSequenceListSql();
  virtual QString getTriggerListSql();
  virtual QString getProcedureListSql();
};

#endif // MYSQLDATABASE_H
