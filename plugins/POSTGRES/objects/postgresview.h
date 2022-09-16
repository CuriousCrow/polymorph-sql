#ifndef POSTGRESVIEW_H
#define POSTGRESVIEW_H

#include "objects/dbview.h"

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

#endif // POSTGRESVIEW_H
