#ifndef QDBFIREBIRDTABLEITEM_H
#define QDBFIREBIRDTABLEITEM_H

#include "../qdbtableitem.h"  

class QDBFirebirdTableItem : public QDBTableItem
{
  Q_OBJECT
public:
  QDBFirebirdTableItem(QString caption, QObject* parent = nullptr);
  ~QDBFirebirdTableItem();
  // QDBObjectItem interface
public:
  virtual bool insertMe();
  virtual bool updateMe();
  // QDBTableItem interface
public:
  virtual void reloadColumnsModel();
private:
  QString createTableQuery(QString table);
  ColumnType colTypeFromString(QString strType);
  QString columnDef(const SqlColumn &col);
};

#endif // QDBFIREBIRDTABLEITEM_H
