#ifndef QDBDATABASEITEM_H
#define QDBDATABASEITEM_H

#include "qdbobjectitem.h"
#include "qsqlqueryhelper.h"

#define DRIVER_FIREBIRD "QIBASE"
#define DRIVER_SQLITE "QSQLITE"
#define DRIVER_POSTGRES "QPSQL"
#define DRIVER_MYSQL "QMYSQL"

class QDBDatabaseItem : public QDBObjectItem
{
  Q_OBJECT
public:
  QDBDatabaseItem(QString caption, QObject* parent = 0);
  ~QDBDatabaseItem();

  bool createDbConnection();
protected:
//  QString fillSqlPattern(QString pattern);
  virtual void loadViewItems(QDBObjectItem* parentItem);
  virtual void loadSequenceItems(QDBObjectItem* parentItem);
  virtual void loadTriggerItems(QDBObjectItem* parentItem);
  virtual void loadProcedureItems(QDBObjectItem* parentItem);
  
  virtual QString getViewListSql();
  virtual QString getSequenceListSql();
  virtual QString getTriggerListSql();
  virtual QString getProcedureListSql();

  QString driver();
  bool isDriver(QString name);
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
