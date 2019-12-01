#ifndef QDBFOREIGNKEY_H
#define QDBFOREIGNKEY_H

#include <QObject>
#include "qdbconstraintitem.h"


class DBForeignKey : public DBConstraintItem
{
  Q_OBJECT
public:
  DBForeignKey(QString caption, QObject* parent = nullptr);

  // QDBObjectItem interface
public:
  virtual int type() override;
  virtual ActionResult insertMe() override;
};

#endif // QDBFOREIGNKEY_H
