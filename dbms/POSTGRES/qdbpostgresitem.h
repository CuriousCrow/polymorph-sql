#ifndef QDBPOSTGRESITEM_H
#define QDBPOSTGRESITEM_H

#include "../qdbdatabaseitem.h"

class QDBPostgresItem : public QDBDatabaseItem
{
  Q_OBJECT
public:
  QDBPostgresItem(QString caption);
  ~QDBPostgresItem();

  // QDBDatabaseItem interface
protected:
  virtual QString getViewListSql();
  virtual QString getSequenceListSql();
  virtual QString getTriggerListSql();
  virtual QString getProcedureListSql();

  // QDBDatabaseItem interface
public:
  virtual QDBTableItem *createNewTableItem(QString caption, QObject *parent);
  virtual QDBSequenceItem *createNewSequenceItem(QString caption, QObject *parent);
  virtual QDBProcedureItem *createNewProcedureItem(QString caption, QObject *parent);
  virtual QDBTriggerItem *createNewTriggerItem(QString caption, QObject *parent);

  // QDBDatabaseItem interface
protected:
  void loadSequenceItems(QDBObjectItem *parentItem);
  void loadTriggerItems(QDBObjectItem *parentItem);
  void loadProcedureItems(QDBObjectItem *parentItem);
};

#endif // QDBPOSTGRESITEM_H
