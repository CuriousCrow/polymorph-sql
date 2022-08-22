#ifndef FIREBIRDPROCEDURE_H
#define FIREBIRDPROCEDURE_H

#include "objects/dbprocedureitem.h"
#include "models/variantmaptablemodel.h"
#include <QObject>

class FirebirdProcedure : public DBProcedureItem
{
  Q_OBJECT
public:
  Q_INVOKABLE FirebirdProcedure();
  ~FirebirdProcedure();

  VariantMapTableModel* inArgModel();
  VariantMapTableModel* outArgModel();

  void addInArg();
  void addOutArg();
  void removeInArg(int row);
  void removeOutArg(int row);

  // DBObjectItem interface
public:
  virtual bool refresh() override;
  virtual QString toDDL() const override;
  virtual ActionResult insertMe() override;
  virtual ActionResult updateMe() override;
private:
  QString argsFromModel(VariantMapTableModel* argModel) const;
  int _inMaxId = 1;
  int _outMaxId = 1;
  VariantMapTableModel* _mInArguments;
  VariantMapTableModel* _mOutArguments;
};

#endif // FIREBIRDPROCEDURE_H
