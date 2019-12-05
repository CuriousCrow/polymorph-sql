#ifndef DBPRIMARYKEY_H
#define DBPRIMARYKEY_H

#include <QObject>
#include "dbconstraintitem.h"

class DBPrimaryKey : public DBConstraintItem
{
  Q_OBJECT
public:
  DBPrimaryKey(QString caption, QObject* parent = nullptr);

  // DBObjectItem interface
public:
  virtual int type() override;
  virtual bool refresh() override;
  virtual ActionResult insertMe() override;
};

#endif // DBPRIMARYKEY_H
