#ifndef QDBMYSQLTABLEITEM_H
#define QDBMYSQLTABLEITEM_H

#include "../qdbtableitem.h"

class DBMysqlTableItem : public DBTableItem
{
  Q_OBJECT
public:
  DBMysqlTableItem(QString caption, QObject* parent = nullptr);
  virtual ~DBMysqlTableItem() override;

  // QDBObjectItem interface
public:
  virtual ActionResult insertMe() override;
  virtual ActionResult updateMe() override;

  // QDBTableItem interface
public:
  virtual void reloadColumnsModel() override;
private:
  QString createTableQuery(QString table);
  QString columnDef(const SqlColumn &col);
};

#endif // QDBMYSQLTABLEITEM_H
