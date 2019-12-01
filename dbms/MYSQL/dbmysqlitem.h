#ifndef DBMYSQLITEM_H
#define DBMYSQLITEM_H

#include "../dbdatabaseitem.h"

class DBMysqlItem : public DBDatabaseItem
{
  Q_OBJECT
public:
  DBMysqlItem(QString caption);
  ~DBMysqlItem();

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

#endif // DBMYSQLITEM_H
