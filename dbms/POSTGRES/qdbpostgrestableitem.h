#ifndef QDBPOSTGRESTABLEITEM_H
#define QDBPOSTGRESTABLEITEM_H

#include "../qdbtableitem.h"

class QDBPostgresTableItem : public QDBTableItem
{
  Q_OBJECT
public:
  QDBPostgresTableItem(QString caption, QObject* parent = 0);
  ~QDBPostgresTableItem();
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

#endif // QDBPOSTGRESTABLEITEM_H
