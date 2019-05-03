#ifndef QDBMYSQLITEM_H
#define QDBMYSQLITEM_H

#include "../qdbdatabaseitem.h"

class QDBMysqlItem : public QDBDatabaseItem
{
  Q_OBJECT
public:
  QDBMysqlItem(QString caption, QObject* parent = nullptr);
  ~QDBMysqlItem();

  virtual QDBTableItem* createNewTableItem(QString caption, QObject* parent = nullptr);
  // QDBObjectItem interface
public:
  virtual bool loadChildren();

  // QDBDatabaseItem interface
protected:
  virtual QString getViewListSql();
  virtual QString getSequenceListSql();
  virtual QString getTriggerListSql();
  virtual QString getProcedureListSql();
};

#endif // QDBMYSQLITEM_H
