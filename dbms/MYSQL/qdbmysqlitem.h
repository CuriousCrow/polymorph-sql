#ifndef QDBMYSQLITEM_H
#define QDBMYSQLITEM_H

#include "../qdbdatabaseitem.h"

class DBMysqlItem : public DBDatabaseItem
{
  Q_OBJECT
public:
  DBMysqlItem(QString caption);
  ~DBMysqlItem();

  virtual DBTableItem* createNewTableItem(QString caption, QObject* parent = nullptr);
  // QDBObjectItem interface
public:
  virtual bool reloadChildren();

  // QDBDatabaseItem interface
protected:
  virtual QString getViewListSql();
  virtual QString getSequenceListSql();
  virtual QString getTriggerListSql();
  virtual QString getProcedureListSql();
};

#endif // QDBMYSQLITEM_H
