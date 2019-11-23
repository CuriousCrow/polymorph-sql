#ifndef QDBPOSTGRESTABLEITEM_H
#define QDBPOSTGRESTABLEITEM_H

#include "../qdbtableitem.h"
#include <QSqlField>

class QDBPostgresTableItem : public QDBTableItem
{
  Q_OBJECT
public:
  QDBPostgresTableItem(QString caption, QObject* parent = nullptr);
  ~QDBPostgresTableItem();
  // QDBObjectItem interface
public:
  virtual ActionResult insertMe();
  virtual ActionResult updateMe();
  // QDBTableItem interface
public:
  virtual void reloadColumnsModel();
protected:
  QString caption();
private:
  QString createTableQuery(QString table);
  QString columnDef(const SqlColumn &col);
  QString typeDef(const SqlColumn &col);
  QString defaultDef(const SqlColumn &col);
};

#endif // QDBPOSTGRESTABLEITEM_H
