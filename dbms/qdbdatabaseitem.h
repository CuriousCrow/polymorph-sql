#ifndef QDBDATABASEITEM_H
#define QDBDATABASEITEM_H

#include "qdbobjectitem.h"
#include "qsqlqueryhelper.h"
#include "qdbtableitem.h"
#include "qdbprocedureitem.h"
#include "qdbsequenceitem.h"
#include "qdbtriggeritem.h"
#include "qdbviewitem.h"

#define DRIVER_FIREBIRD "QIBASE"
#define DRIVER_SQLITE "QSQLITE"
#define DRIVER_POSTGRES "QPSQL"
#define DRIVER_MYSQL "QMYSQL"

class QDBDatabaseItem : public QDBObjectItem
{
  Q_OBJECT
public:
  QDBDatabaseItem(QString caption);
  ~QDBDatabaseItem();

  bool createDbConnection();
  virtual QDBTableItem* createNewTableItem(QString caption, QObject* parent = nullptr);
  virtual QDBViewItem* createNewViewItem(QString caption, QObject* parent = nullptr);
  virtual QDBProcedureItem* createNewProcedureItem(QString caption, QObject* parent = nullptr);
  virtual QDBSequenceItem* createNewSequenceItem(QString caption, QObject* parent = nullptr);
  virtual QDBTriggerItem* createNewTriggerItem(QString caption, QObject* parent = nullptr);
protected:
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
  virtual bool reloadChildren();
  virtual QUrl objectUrl();
  virtual ActionResult insertMe();
  virtual ActionResult updateMe();
  virtual ActionResult deleteMe();

  // LAbstractTreeItem interface
public:  
  virtual QVariant colData(int column, int role);
  virtual int type();
};

#endif // QDBDATABASEITEM_H
