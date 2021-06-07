#ifndef POSTGRESVIEWITEM_H
#define POSTGRESVIEWITEM_H

#include "sdk/objects/dbviewitem.h"

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
