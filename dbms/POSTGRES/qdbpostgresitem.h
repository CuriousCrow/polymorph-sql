#ifndef QDBPOSTGRESITEM_H
#define QDBPOSTGRESITEM_H

#include "../qdbdatabaseitem.h"

class DBPostgresItem : public DBDatabaseItem
{
  Q_OBJECT
public:
  DBPostgresItem(QString caption);
  ~DBPostgresItem();

  // QDBDatabaseItem interface
protected:
  virtual QString getViewListSql();
  virtual QString getSequenceListSql();
  virtual QString getTriggerListSql();
  virtual QString getProcedureListSql();

  // QDBDatabaseItem interface
public:
  virtual DBTableItem *createNewTableItem(QString caption, QObject *parent);
  virtual DBSequenceItem *createNewSequenceItem(QString caption, QObject *parent);
  virtual DBProcedureItem *createNewProcedureItem(QString caption, QObject *parent);
  virtual DBTriggerItem *createNewTriggerItem(QString caption, QObject *parent);

  // QDBDatabaseItem interface
protected:
  void loadSequenceItems(DBObjectItem *parentItem);
  void loadTriggerItems(DBObjectItem *parentItem);
  void loadProcedureItems(DBObjectItem *parentItem);
};

#endif // QDBPOSTGRESITEM_H
