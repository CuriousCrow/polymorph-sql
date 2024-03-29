#ifndef POSTGRESTABLE_H
#define POSTGRESTABLE_H

#include <QSqlField>
#include "objects/dbtableitem.h"

/** PostgreSQL table item */
class PostgresTable : public DBTableItem
{
  Q_OBJECT
public:
  Q_INVOKABLE PostgresTable();
  virtual ~PostgresTable() Q_DECL_OVERRIDE;

  INJECT_INITIALIZE(SqlColumnModel*, _columnsModel, baseColumnModel)

  virtual DBForeignKey* newForeignKey() Q_DECL_OVERRIDE;
  virtual DBPrimaryKey* newPrimaryKey() Q_DECL_OVERRIDE;
  virtual DBUniqueConstraint* newUniqueConstraint() Q_DECL_OVERRIDE;
  virtual DBCheckConstraint* newCheckConstraint() Q_DECL_OVERRIDE;
  // DBObjectItem interface
public:
  virtual ActionResult insertMe() Q_DECL_OVERRIDE;
  virtual ActionResult updateMe() Q_DECL_OVERRIDE;
  virtual QString toDDL() const Q_DECL_OVERRIDE;
  // DBTableItem interface
public:
  virtual void reloadColumnsModel() Q_DECL_OVERRIDE;
  virtual void reloadConstraintsModel() Q_DECL_OVERRIDE;
private:
  QString createTableQuery(QString table) const;
  QString columnDef(const SqlColumn &col) const;
  QString typeDef(const SqlColumn &col) const;
};

#endif // POSTGRESTABLE_H
