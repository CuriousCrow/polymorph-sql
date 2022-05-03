#ifndef DBMYSQLTABLEITEM_H
#define DBMYSQLTABLEITEM_H

#include "objects/dbtableitem.h"

//TODO: MySQL uses  backtick (`) character for quotation

class MysqlTableItem : public DBTableItem
{
  Q_OBJECT
public:
  Q_INVOKABLE MysqlTableItem();
  virtual ~MysqlTableItem() Q_DECL_OVERRIDE;

  INJECT_INITIALIZE(SqlColumnModel*, _columnsModel, baseColumnModel)

  // DBObjectItem interface
public:
  virtual ActionResult insertMe() Q_DECL_OVERRIDE;
  virtual ActionResult updateMe() Q_DECL_OVERRIDE;

  // DBTableItem interface
public:
  virtual void reloadColumnsModel() Q_DECL_OVERRIDE;
private:
  QString createTableQuery(QString table) const;
  QString columnDef(const SqlColumn &col) const;
};

#endif // DBMYSQLTABLEITEM_H
