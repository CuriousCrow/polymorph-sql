#ifndef POSTGRESTABLE_H
#define POSTGRESTABLE_H

#include "../dbtableitem.h"
#include <QSqlField>

class PostgresTable : public DBTableItem
{
  Q_OBJECT
public:
  PostgresTable(QString caption, QObject* parent = nullptr);
  virtual ~PostgresTable() override;

  virtual DBForeignKey* newForeignKey() override;
  virtual DBPrimaryKey* newPrimaryKey() override;
  virtual DBUniqueConstraint* newUniqueConstraint() override;
  virtual DBCheckConstraint* newCheckConstraint() override;
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

#endif // POSTGRESTABLE_H
