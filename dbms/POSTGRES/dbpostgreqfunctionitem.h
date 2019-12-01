#ifndef DBPOSTGREQFUNCTIONITEM_H
#define DBPOSTGREQFUNCTIONITEM_H

#include <QObject>
#include "../dbprocedureitem.h"

class DBPostgreqFunctionItem : public DBProcedureItem
{
  Q_OBJECT
public:
  DBPostgreqFunctionItem(QString caption, QObject* parent = nullptr);

  // DBObjectItem interface
public:
  virtual bool refresh() override;
  virtual ActionResult insertMe() override;
  virtual ActionResult updateMe() override;
  virtual ActionResult deleteMe() override;
};

#endif // DBPOSTGREQFUNCTIONITEM_H
