#ifndef SQLITEVIEW_H
#define SQLITEVIEW_H

#include <QObject>
#include "objects/dbview.h"

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

#endif // SQLITEVIEW_H
