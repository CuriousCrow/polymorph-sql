#ifndef QDBCONSTRAINTITEM_H
#define QDBCONSTRAINTITEM_H

#include <QObject>
#include "qdbobjectitem.h"

class DBConstraintItem : public DBObjectItem
{
  Q_OBJECT
public:
  DBConstraintItem(QString caption, QObject* parent = nullptr);

  // QDBObjectItem interface
public:
  virtual bool reloadChildren() override;
  virtual int type() override;
  virtual ActionResult deleteMe() override;
  virtual ActionResult updateMe() override;
};

#endif // QDBCONSTRAINTITEM_H
