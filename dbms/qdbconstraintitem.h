#ifndef QDBCONSTRAINTITEM_H
#define QDBCONSTRAINTITEM_H

#include <QObject>
#include "qdbobjectitem.h"

class QDBConstraintItem : public QDBObjectItem
{
  Q_OBJECT
public:
  QDBConstraintItem(QString caption, QObject* parent = nullptr);

  // QDBObjectItem interface
public:
  virtual bool loadChildren() override;
  virtual int type() override;
  virtual ActionResult deleteMe() override;
  virtual ActionResult updateMe() override;
};

#endif // QDBCONSTRAINTITEM_H
