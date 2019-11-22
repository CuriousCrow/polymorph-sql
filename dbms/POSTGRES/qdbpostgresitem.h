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
  virtual QDBTableItem *createNewTableItem(QString caption, QUrl url, QObject *parent);
  virtual QDBSequenceItem *createNewSequenceItem(QString caption, QUrl url, QObject *parent);
  virtual QDBProcedureItem *createNewProcedureItem(QString caption, QUrl url, QObject *parent);
  virtual QDBTriggerItem *createNewTriggerItem(QString caption, QUrl url, QObject *parent);

  // QDBDatabaseItem interface
protected:
  void loadViewItems(QDBObjectItem *parentItem);
  void loadSequenceItems(QDBObjectItem *parentItem);
  void loadTriggerItems(QDBObjectItem *parentItem);
  void loadProcedureItems(QDBObjectItem *parentItem);
};

#endif // QDBPOSTGRESITEM_H
