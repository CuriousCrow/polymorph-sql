#ifndef QDBFIREBIRDITEM_H
#define QDBFIREBIRDITEM_H

#include <QObject>
#include "../qdbdatabaseitem.h"

class QDBFirebirdItem : public QDBDatabaseItem
{
  Q_OBJECT
public:
  QDBFirebirdItem(QString caption, QObject* parent = 0);

  // QDBDatabaseItem interface
protected:
  virtual QString getViewListSql();
  virtual QString getSequenceListSql();
  virtual QString getTriggerListSql();
  virtual QString getProcedureListSql();
};

#endif // QDBFIREBIRDITEM_H
