#ifndef QDBFIREBIRDTABLEITEM_H
#define QDBFIREBIRDTABLEITEM_H

#include "../qdbtableitem.h"  

class DBFirebirdTableItem : public DBTableItem
{
  Q_OBJECT
public:
  DBFirebirdTableItem(QString caption, QObject* parent = nullptr);
  virtual ~DBFirebirdTableItem() override;
  // QDBTableItem interface
public:
  virtual void reloadColumnsModel() override;
private:
  QString createTableQuery(QString table);
  QString columnDef(const SqlColumn &col);
};

#endif // QDBFIREBIRDTABLEITEM_H
