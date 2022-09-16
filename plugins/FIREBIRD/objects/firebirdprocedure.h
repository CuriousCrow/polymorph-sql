#ifndef FIREBIRDPROCEDURE_H
#define FIREBIRDPROCEDURE_H

#include "objects/dbprocedure.h"
#include "models/variantmaptablemodel.h"
#include "firebirdtypeprovider.h"
#include <QObject>
#include "core/core.h"
#include "firebirdconst.h"

class ArgumentTableModel : public VariantMapTableModel
{
  Q_OBJECT
public:
  Q_INVOKABLE ArgumentTableModel();

  INJECT(FirebirdTypeProvider*, firebirdTypeProvider)

public slots:
  void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>());

  // VariantMapTableModel interface
public:
  virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
private:
  bool hasLength(int row) const;
};

class FirebirdProcedure : public DBProcedureItem
{
  Q_OBJECT
public:
  Q_INVOKABLE FirebirdProcedure();
  ~FirebirdProcedure();

  ArgumentTableModel* inArgumentModel();
  ArgumentTableModel* outArgumentModel();

  INJECT_AS(ArgumentTableModel*, inArgModel, firebirdArgModel)
  INJECT_AS(ArgumentTableModel*, outArgModel, firebirdArgModel)

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
};

#endif // FIREBIRDPROCEDURE_H
