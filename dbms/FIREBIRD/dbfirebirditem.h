#ifndef DBFIREBIRDITEM_H
#define DBFIREBIRDITEM_H

#include <QObject>
#include "../dbdatabaseitem.h"

class DBFirebirdItem : public DBDatabaseItem
{
  Q_OBJECT
public:
  DBFirebirdItem(QString caption);

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

#endif // DBFIREBIRDITEM_H
