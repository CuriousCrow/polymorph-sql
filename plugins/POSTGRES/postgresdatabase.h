#ifndef POSTGRESDATABASE_H
#define POSTGRESDATABASE_H

#include "sdk/objects/dbdatabaseitem.h"

class PostgresDatabase : public DBDatabaseItem
{
  Q_OBJECT
public:
  PostgresDatabase(QString caption);
  ~PostgresDatabase();

  // DBDatabaseItem interface
protected:
  virtual QString getViewListSql() const Q_DECL_OVERRIDE;
  virtual QString getSequenceListSql() const Q_DECL_OVERRIDE;
  virtual QString getTriggerListSql() const Q_DECL_OVERRIDE;
  virtual QString getProcedureListSql() const Q_DECL_OVERRIDE;

  // DBDatabaseItem interface
public:
  virtual DBTableItem *createNewTableItem(QString caption, QObject *parent) Q_DECL_OVERRIDE;
  virtual DBSequenceItem *createNewSequenceItem(QString caption, QObject *parent) Q_DECL_OVERRIDE;
  virtual DBProcedureItem *createNewProcedureItem(QString caption, QObject *parent) Q_DECL_OVERRIDE;
  virtual DBTriggerItem *createNewTriggerItem(QString caption, QObject *parent) Q_DECL_OVERRIDE;
  virtual QString getAllObjectListSql() const Q_DECL_OVERRIDE;

  // DBDatabaseItem interface
protected:
  void loadSequenceItems(DBObjectItem *parentItem) Q_DECL_OVERRIDE;
  void loadTriggerItems(DBObjectItem *parentItem) Q_DECL_OVERRIDE;
  void loadProcedureItems(DBObjectItem *parentItem) Q_DECL_OVERRIDE;
};

#endif // POSTGRESDATABASE_H
