#ifndef MYSQLPROCEDURE_H
#define MYSQLPROCEDURE_H

#include "objects/dbprocedureitem.h"
#include <QObject>
#include "models/variantmaptablemodel.h"

class MysqlProcedure : public DBProcedureItem
{
  Q_OBJECT
public:
  Q_INVOKABLE MysqlProcedure();
  ~MysqlProcedure();

  // DBObjectItem interface
public:
  virtual bool refresh() override;
  virtual QString toDDL() const override;
  virtual ActionResult insertMe() override;

public:
  VariantMapTableModel* argumentModel();
private:
  void refreshArguments();
  QString argsFromModel() const;
  VariantMapTableModel* _mArguments;
};

#endif // MYSQLPROCEDURE_H
