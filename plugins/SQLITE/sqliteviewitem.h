#ifndef SQLITEVIEWITEM_H
#define SQLITEVIEWITEM_H

#include <QObject>
#include "sdk/objects/dbviewitem.h"

class SqliteViewItem : public DBViewItem
{
  Q_OBJECT
public:
  SqliteViewItem(QString caption, QObject* parent = nullptr);

  // DBObjectItem interface
public:
  virtual bool refresh() Q_DECL_OVERRIDE;
};

#endif // SQLITEVIEWITEM_H
