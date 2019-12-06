#ifndef DBMYSQLTABLEITEM_H
#define DBMYSQLTABLEITEM_H

#include "../dbtableitem.h"

class DBMysqlTableItem : public DBTableItem
{
  Q_OBJECT
public:
  DBMysqlTableItem(QString caption, QObject* parent = nullptr);
  virtual ~DBMysqlTableItem() override;

  // DBObjectItem interface
public:
  virtual ActionResult insertMe() override;
  virtual ActionResult updateMe() override;

  // DBTableItem interface
public:
  virtual void reloadColumnsModel() override;
private:
  QString createTableQuery(QString table);
  QString columnDef(const SqlColumn &col);
};

#endif // DBMYSQLTABLEITEM_H
