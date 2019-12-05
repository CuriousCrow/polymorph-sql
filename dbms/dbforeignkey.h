#ifndef DBFOREIGNKEY_H
#define DBFOREIGNKEY_H

#include <QObject>
#include "dbconstraintitem.h"


class DBForeignKey : public DBConstraintItem
{
  Q_OBJECT
public:
  DBForeignKey(QString caption, QObject* parent = nullptr);

  // DBObjectItem interface
public:
  virtual int type() override;
  virtual ActionResult insertMe() override;
  virtual bool refresh() override;
};

#endif // DBFOREIGNKEY_H
