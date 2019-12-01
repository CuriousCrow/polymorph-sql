#ifndef QDBPOSTGREQFUNCTIONITEM_H
#define QDBPOSTGREQFUNCTIONITEM_H

#include <QObject>
#include "../qdbprocedureitem.h"

class DBPostgreqFunctionItem : public DBProcedureItem
{
  Q_OBJECT
public:
  DBPostgreqFunctionItem(QString caption, QObject* parent = nullptr);

  // QDBObjectItem interface
public:
  virtual bool refresh() override;
  virtual ActionResult insertMe() override;
  virtual ActionResult updateMe() override;
  virtual ActionResult deleteMe() override;
};

#endif // QDBPOSTGREQFUNCTIONITEM_H
