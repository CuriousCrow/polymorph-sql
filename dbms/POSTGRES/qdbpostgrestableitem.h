#ifndef QDBPOSTGRESTABLEITEM_H
#define QDBPOSTGRESTABLEITEM_H

#include "../qdbtableitem.h"
#include <QSqlField>

class QDBPostgresTableItem : public QDBTableItem
{
  Q_OBJECT
public:
  QDBPostgresTableItem(QString caption, QObject* parent = nullptr);
  virtual ~QDBPostgresTableItem() override;
  // QDBObjectItem interface
public:
  virtual ActionResult insertMe() override;
  virtual ActionResult updateMe() override;
  // QDBTableItem interface
public:
  virtual void reloadColumnsModel() override;
protected:
  QString caption();
private:
  QString createTableQuery(QString table);
  QString columnDef(const SqlColumn &col);
  QString typeDef(const SqlColumn &col);
  QString defaultDef(const SqlColumn &col);

  // QDBTableItem interface
public:
  virtual void reloadConstraintsModel() override;
};

#endif // QDBPOSTGRESTABLEITEM_H
