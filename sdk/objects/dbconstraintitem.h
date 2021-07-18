#ifndef DBCONSTRAINTITEM_H
#define DBCONSTRAINTITEM_H

#include <QObject>
#include "dbobjectitem.h"

class DBConstraintItem : public DBObjectItem
{
  Q_OBJECT
public:
  DBConstraintItem(QString caption, QObject* parent = nullptr);

  // DBObjectItem interface
public:
  virtual bool reloadChildren() Q_DECL_OVERRIDE;
  virtual int type() const Q_DECL_OVERRIDE;
  virtual ActionResult deleteMe() Q_DECL_OVERRIDE;
  virtual ActionResult updateMe() Q_DECL_OVERRIDE;
};

#endif // DBCONSTRAINTITEM_H
