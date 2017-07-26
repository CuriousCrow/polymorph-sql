#ifndef QDBMYSQLTABLEITEM_H
#define QDBMYSQLTABLEITEM_H

#include "../qdbtableitem.h"

class QDBMysqlTableItem : public QDBTableItem
{
  Q_OBJECT
public:
  QDBMysqlTableItem(QString caption, QObject* parent = 0);
  ~QDBMysqlTableItem();

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

#endif // QDBMYSQLTABLEITEM_H
