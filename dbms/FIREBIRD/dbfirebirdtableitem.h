#ifndef DBFIREBIRDTABLEITEM_H
#define DBFIREBIRDTABLEITEM_H

#include "../dbtableitem.h"

class DBFirebirdTableItem : public DBTableItem
{
  Q_OBJECT
public:
  DBFirebirdTableItem(QString caption, QObject* parent = nullptr);
  virtual ~DBFirebirdTableItem() override;
  // DBTableItem interface
public:
  virtual void reloadColumnsModel() override;
private:
  QString createTableQuery(QString table);
  QString columnDef(const SqlColumn &col);
};

#endif // DBFIREBIRDTABLEITEM_H
