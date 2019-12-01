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
  virtual QUrl objectUrl();
  virtual ActionResult insertMe();
  virtual ActionResult updateMe();
  virtual ActionResult deleteMe();

  // LAbstractTreeItem interface
public:  
  virtual QVariant colData(int column, int role);
  virtual int type();

public slots:
  void onFolderRequestReload();
};

#endif // QDBDATABASEITEM_H
