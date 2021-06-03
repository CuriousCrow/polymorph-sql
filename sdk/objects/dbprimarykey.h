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
  virtual int type() const Q_DECL_OVERRIDE;
  virtual bool refresh() Q_DECL_OVERRIDE;
  virtual ActionResult insertMe() Q_DECL_OVERRIDE;
};

#endif // DBPRIMARYKEY_H
