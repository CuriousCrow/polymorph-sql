#ifndef DBDATABASE_H
#define DBDATABASE_H

#include "dbobjectitem.h"

class DBDatabaseItem : public DBObjectItem
{
  Q_OBJECT
public:
  Q_INVOKABLE DBDatabaseItem(QString caption = "");
  ~DBDatabaseItem() Q_DECL_OVERRIDE;

  bool createDbConnection();
  QString info();

  DBObjectItem* folderByType(DBObjectItem::ItemType type);
protected:
  QString driver() const;

  // DBObjectItem interface
public:
  virtual ObjectStatus status() const Q_DECL_OVERRIDE;
  virtual bool reloadChildren() Q_DECL_OVERRIDE;
  virtual AppUrl objectUrl() Q_DECL_OVERRIDE;
  virtual ActionResult insertMe() Q_DECL_OVERRIDE;
  virtual ActionResult updateMe() Q_DECL_OVERRIDE;
  virtual ActionResult deleteMe() Q_DECL_OVERRIDE;

  virtual ActionResult createDatabase();
  virtual ActionResult dropDatabase();

  virtual QString getAllObjectListSql() const;

  // LAbstractTreeItem interface
public:  
  virtual QVariant colData(int column, int role) const Q_DECL_OVERRIDE;
  virtual int type() const Q_DECL_OVERRIDE;
};

#endif // DBDATABASE_H
