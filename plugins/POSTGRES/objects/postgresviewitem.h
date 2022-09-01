#ifndef POSTGRESVIEWITEM_H
#define POSTGRESVIEWITEM_H

#include "objects/dbviewitem.h"

/** PostgreSQL view item */
class PostgresViewItem : public DBViewItem
{
  Q_OBJECT
public:
  Q_INVOKABLE PostgresViewItem();

  // DBObjectItem interface
public:
  virtual bool refresh() override;
};

#endif // POSTGRESVIEWITEM_H
