#ifndef QDBDATABASEITEM_H
#define QDBDATABASEITEM_H

#include "qdbobjectitem.h"
#include "qsqlqueryhelper.h"

class QDBDatabaseItem : public QDBObjectItem
{
  Q_OBJECT
public:
  QDBDatabaseItem(QString caption, QObject* parent = 0);
  ~QDBDatabaseItem();

  bool createDbConnection();

protected:
  QString fillSqlPattern(QString pattern);
  void loadViewItems(QDBObjectItem* parentItem);
  void loadSequenceItems(QDBObjectItem* parentItem);
  void loadTriggerItems(QDBObjectItem* parentItem);
  void loadProcedureItems(QDBObjectItem* parentItem);

  // QDBObjectItem interface
public:
  virtual bool loadChildren();
  virtual QUrl objectUrl();  
  virtual bool insertMe();
  virtual bool updateMe();
  virtual bool deleteMe();

  // LAbstractTreeItem interface
public:  
  virtual QVariant colData(int column, int role);
  virtual int type();
};

#endif // QDBDATABASEITEM_H
