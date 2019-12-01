#ifndef DBPOSTGRESTABLEITEM_H
#define DBPOSTGRESTABLEITEM_H

#include "../dbtableitem.h"
#include <QSqlField>

class DBPostgresTableItem : public DBTableItem
{
  Q_OBJECT
public:
  DBPostgresTableItem(QString caption, QObject* parent = nullptr);
  virtual ~DBPostgresTableItem() override;
  // DBObjectItem interface
public:
  virtual ActionResult insertMe() override;
  virtual ActionResult updateMe() override;
  // DBTableItem interface
public:
  virtual void reloadColumnsModel() override;
protected:
  QString caption();
private:
  QString createTableQuery(QString table);
  QString columnDef(const SqlColumn &col);
  QString typeDef(const SqlColumn &col);
  QString defaultDef(const SqlColumn &col);

  // DBTableItem interface
public:
  virtual void reloadConstraintsModel() override;
};

#endif // DBPOSTGRESTABLEITEM_H
