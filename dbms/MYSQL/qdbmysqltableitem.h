#ifndef QDBMYSQLTABLEITEM_H
#define QDBMYSQLTABLEITEM_H

#include "../qdbtableitem.h"

class QDBMysqlTableItem : public QDBTableItem
{
  Q_OBJECT
public:
  QDBMysqlTableItem(QString caption, QObject* parent = nullptr);
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
  QString columnDef(const SqlColumn &col);
};

#endif // QDBMYSQLTABLEITEM_H
