#ifndef DBPOSTGRESITEM_H
#define DBPOSTGRESITEM_H

#include "../dbdatabaseitem.h"

class DBPostgresItem : public DBDatabaseItem
{
  Q_OBJECT
public:
  DBPostgresItem(QString caption);
  ~DBPostgresItem();

  // DBDatabaseItem interface
protected:
  virtual QString getViewListSql();
  virtual QString getSequenceListSql();
  virtual QString getTriggerListSql();
  virtual QString getProcedureListSql();

  // DBDatabaseItem interface
public:
  virtual DBTableItem *createNewTableItem(QString caption, QObject *parent);
  virtual DBSequenceItem *createNewSequenceItem(QString caption, QObject *parent);
  virtual DBProcedureItem *createNewProcedureItem(QString caption, QObject *parent);
  virtual DBTriggerItem *createNewTriggerItem(QString caption, QObject *parent);

  // DBDatabaseItem interface
protected:
  void loadSequenceItems(DBObjectItem *parentItem);
  void loadTriggerItems(DBObjectItem *parentItem);
  void loadProcedureItems(DBObjectItem *parentItem);
};

#endif // DBPOSTGRESITEM_H
