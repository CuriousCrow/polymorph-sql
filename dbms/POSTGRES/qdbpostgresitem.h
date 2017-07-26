#ifndef QDBPOSTGRESITEM_H
#define QDBPOSTGRESITEM_H

#include "../qdbdatabaseitem.h"

class QDBPostgresItem : public QDBDatabaseItem
{
  Q_OBJECT
public:
  QDBPostgresItem(QString caption, QObject* parent = 0);
  ~QDBPostgresItem();

  // QDBDatabaseItem interface
protected:
  virtual QString getViewListSql();
  virtual QString getSequenceListSql();
  virtual QString getTriggerListSql();
  virtual QString getProcedureListSql();
};

#endif // QDBPOSTGRESITEM_H
