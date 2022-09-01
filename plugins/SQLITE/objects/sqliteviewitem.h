#ifndef SQLITEVIEWITEM_H
#define SQLITEVIEWITEM_H

#include <QObject>
#include "objects/dbviewitem.h"

/** SQLite view item */
class SqliteViewItem : public DBViewItem
{
  Q_OBJECT
public:
  Q_INVOKABLE SqliteViewItem();

  // DBObjectItem interface
public:
  virtual bool refresh() Q_DECL_OVERRIDE;
};

#endif // SQLITEVIEWITEM_H
