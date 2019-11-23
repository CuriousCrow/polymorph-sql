#ifndef QDBMYSQLTABLEITEM_H
#define QDBMYSQLTABLEITEM_H

#include "../qdbtableitem.h"

class QDBMysqlTableItem : public QDBTableItem
{
  Q_OBJECT
public:
  QDBMysqlTableItem(QString caption, QObject* parent = nullptr);
  virtual ~QDBMysqlTableItem() override;

  // QDBObjectItem interface
public:
  virtual ActionResult insertMe() override;
  virtual ActionResult updateMe() override;

  // QDBTableItem interface
public:
  virtual void reloadColumnsModel() override;
private:
  QString createTableQuery(QString table);
  QString columnDef(const SqlColumn &col);
};

#endif // QDBMYSQLTABLEITEM_H
