#ifndef DBFOREIGNKEY_H
#define DBFOREIGNKEY_H

#include <QObject>
#include "dbconstraintitem.h"


class DBForeignKey : public DBConstraintItem
{
  Q_OBJECT
public:
  Q_INVOKABLE DBForeignKey(QString caption = "", QObject* parent = nullptr);

  // DBObjectItem interface
public:
  virtual int type() const Q_DECL_OVERRIDE;
  virtual ActionResult insertMe() Q_DECL_OVERRIDE;
  virtual QString toDDL() const Q_DECL_OVERRIDE;
  virtual bool refresh() Q_DECL_OVERRIDE;
protected:
  virtual QString fillSqlPatternWithFields(QString pattern) const Q_DECL_OVERRIDE;
};

#endif // DBFOREIGNKEY_H
