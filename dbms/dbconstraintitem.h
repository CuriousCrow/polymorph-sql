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
  virtual bool reloadChildren() override;
  virtual int type() override;
  virtual ActionResult deleteMe() override;
  virtual ActionResult updateMe() override;
};

#endif // DBCONSTRAINTITEM_H
