#ifndef FIREBIRDTABLE_H
#define FIREBIRDTABLE_H

#include "../dbtableitem.h"

class FirebirdTable : public DBTableItem
{
  Q_OBJECT
public:
  FirebirdTable(QString caption, QObject* parent = nullptr);
  virtual ~FirebirdTable() override;
  // DBTableItem interface
public:
  virtual void reloadColumnsModel() override;
private:
  QString createTableQuery(QString table);
  QString columnDef(const SqlColumn &col);
};

#endif // FIREBIRDTABLE_H
