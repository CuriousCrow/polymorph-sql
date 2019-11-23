#ifndef QDBFIREBIRDTABLEITEM_H
#define QDBFIREBIRDTABLEITEM_H

#include "../qdbtableitem.h"  

class QDBFirebirdTableItem : public QDBTableItem
{
  Q_OBJECT
public:
  QDBFirebirdTableItem(QString caption, QObject* parent = nullptr);
  virtual ~QDBFirebirdTableItem() override;
  // QDBTableItem interface
public:
  virtual void reloadColumnsModel() override;
private:
  QString createTableQuery(QString table);
  QString columnDef(const SqlColumn &col);
};

#endif // QDBFIREBIRDTABLEITEM_H
