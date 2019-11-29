#ifndef QDBFOREIGNKEY_H
#define QDBFOREIGNKEY_H

#include <QObject>
#include "qdbconstraintitem.h"


class QDBForeignKey : public QDBConstraintItem
{
  Q_OBJECT
public:
  QDBForeignKey(QString caption, QObject* parent = nullptr);

  // QDBObjectItem interface
public:
  virtual int type() override;
  virtual ActionResult insertMe() override;
};

#endif // QDBFOREIGNKEY_H
