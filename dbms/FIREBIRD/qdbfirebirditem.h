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
  virtual QString getViewListSql() override;
  virtual QString getSequenceListSql() override;
  virtual QString getTriggerListSql() override;
  virtual QString getProcedureListSql() override;

  // QDBDatabaseItem interface
public:
  virtual QDBTableItem *createNewTableItem(QString caption, QObject *parent) override;

  // QDBDatabaseItem interface
protected:
  virtual void loadSequenceItems(QDBObjectItem *parentItem) override;
};

#endif // QDBFIREBIRDITEM_H
