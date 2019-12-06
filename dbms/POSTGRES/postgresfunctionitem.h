#ifndef POSTGRESFUNCTIONITEM_H
#define POSTGRESFUNCTIONITEM_H

#include <QObject>
#include "../dbprocedureitem.h"

class PostgresFunctionItem : public DBProcedureItem
{
  Q_OBJECT
public:
  PostgresFunctionItem(QString caption, QObject* parent = nullptr);

  // DBObjectItem interface
public:
  virtual bool refresh() override;
  virtual ActionResult insertMe() override;
  virtual ActionResult updateMe() override;
  virtual ActionResult deleteMe() override;
};

#endif // POSTGRESFUNCTIONITEM_H
