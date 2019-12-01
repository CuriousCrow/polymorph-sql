#ifndef QDBFIREBIRDITEM_H
#define QDBFIREBIRDITEM_H

#include <QObject>
#include "../qdbdatabaseitem.h"

class DBFirebirdItem : public DBDatabaseItem
{
  Q_OBJECT
public:
  DBFirebirdItem(QString caption);

  // QDBDatabaseItem interface
protected:
  virtual QString getViewListSql() override;
  virtual QString getSequenceListSql() override;
  virtual QString getTriggerListSql() override;
  virtual QString getProcedureListSql() override;

  // QDBDatabaseItem interface
public:
  virtual DBTableItem *createNewTableItem(QString caption, QObject *parent) override;

  // QDBDatabaseItem interface
protected:
  virtual void loadSequenceItems(DBObjectItem *parentItem) override;
};

#endif // QDBFIREBIRDITEM_H
