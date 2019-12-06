#ifndef FIREBIRDDATABASE_H
#define FIREBIRDDATABASE_H

#include <QObject>
#include "../dbdatabaseitem.h"

class FirebirdDatabase : public DBDatabaseItem
{
  Q_OBJECT
public:
  FirebirdDatabase(QString caption);

  // DBDatabaseItem interface
protected:
  virtual QString getViewListSql() override;
  virtual QString getSequenceListSql() override;
  virtual QString getTriggerListSql() override;
  virtual QString getProcedureListSql() override;

  // DBDatabaseItem interface
public:
  virtual DBTableItem *createNewTableItem(QString caption, QObject *parent) override;

  // DBDatabaseItem interface
protected:
  virtual void loadSequenceItems(DBObjectItem *parentItem) override;
};

#endif // FIREBIRDDATABASE_H
