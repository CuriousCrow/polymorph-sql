#ifndef QDBFIREBIRDITEM_H
#define QDBFIREBIRDITEM_H

#include <QObject>
#include "../qdbdatabaseitem.h"

class QDBFirebirdItem : public QDBDatabaseItem
{
  Q_OBJECT
public:
  QDBFirebirdItem(QString caption);

  // QDBDatabaseItem interface
protected:
  virtual QString getViewListSql();
  virtual QString getSequenceListSql();
  virtual QString getTriggerListSql();
  virtual QString getProcedureListSql();

  // QDBDatabaseItem interface
public:
  virtual QDBTableItem *createNewTableItem(QString caption, QObject *parent);
};

#endif // QDBFIREBIRDITEM_H
