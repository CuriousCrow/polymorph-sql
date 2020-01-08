#ifndef DBDATABASEITEM_H
#define DBDATABASEITEM_H

#include "dbobjectitem.h"
#include "qsqlqueryhelper.h"
#include "dbtableitem.h"
#include "dbprocedureitem.h"
#include "dbsequenceitem.h"
#include "dbtriggeritem.h"
#include "dbviewitem.h"

#define DRIVER_FIREBIRD "QIBASE"
#define DRIVER_SQLITE "QSQLITE"
#define DRIVER_POSTGRES "QPSQL"
#define DRIVER_MYSQL "QMYSQL"

class DBDatabaseItem : public DBObjectItem
{
  Q_OBJECT
public:
  DBDatabaseItem(QString caption);
  ~DBDatabaseItem();

  bool createDbConnection();
  virtual DBTableItem* createNewTableItem(QString caption, QObject* parent = nullptr);
  virtual DBViewItem* createNewViewItem(QString caption, QObject* parent = nullptr);
  virtual DBProcedureItem* createNewProcedureItem(QString caption, QObject* parent = nullptr);
  virtual DBSequenceItem* createNewSequenceItem(QString caption, QObject* parent = nullptr);
  virtual DBTriggerItem* createNewTriggerItem(QString caption, QObject* parent = nullptr);
protected:
  virtual void loadTableItems(DBObjectItem* parentItem);
  virtual void loadViewItems(DBObjectItem* parentItem);
  virtual void loadSequenceItems(DBObjectItem* parentItem);
  virtual void loadTriggerItems(DBObjectItem* parentItem);
  virtual void loadProcedureItems(DBObjectItem* parentItem);
  
  virtual QString getViewListSql();
  virtual QString getSequenceListSql();
  virtual QString getTriggerListSql();
  virtual QString getProcedureListSql();

  QString driver();
  bool isDriver(QString name);
  // DBObjectItem interface
public:
  virtual bool reloadChildren();
  virtual AppUrl objectUrl();
  virtual ActionResult insertMe();
  virtual ActionResult updateMe();
  virtual ActionResult deleteMe();

  virtual ActionResult createDatabase();
  virtual ActionResult dropDatabase();

  // LAbstractTreeItem interface
public:  
  virtual QVariant colData(int column, int role);
  virtual int type();

public slots:
  void onFolderRequestReload();
};

#endif // DBDATABASEITEM_H
