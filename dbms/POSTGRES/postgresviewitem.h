#ifndef POSTGRESVIEWITEM_H
#define POSTGRESVIEWITEM_H

#include "../dbviewitem.h"

class PostgresViewItem : public DBViewItem
{
  Q_OBJECT
public:
  PostgresViewItem(QString caption, QObject* parent = nullptr);

  // DBObjectItem interface
public:
  virtual bool refresh() override;
};

#endif // POSTGRESVIEWITEM_H
