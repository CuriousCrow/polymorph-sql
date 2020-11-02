#ifndef DBMYSQLTABLEITEM_H
#define DBMYSQLTABLEITEM_H

#include "../dbtableitem.h"

class MysqlTableItem : public DBTableItem
{
  Q_OBJECT
public:
  MysqlTableItem(QString caption, QObject* parent = nullptr);
  virtual ~MysqlTableItem() Q_DECL_OVERRIDE;

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
