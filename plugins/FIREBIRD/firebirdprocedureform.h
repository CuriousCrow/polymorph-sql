#ifndef FIREBIRDPROCEDUREFORM_H
#define FIREBIRDPROCEDUREFORM_H

#include "forms/abstractdatabaseitemform.h"
#include "tools/sqleditorsupport.h"
#include "firebirdprocedure.h"
#include "firebirdtypeprovider.h"
#include "models/comboboxitemdelegate.h"


namespace Ui {
class FirebirdProcedureForm;
}

class FirebirdProcedureForm : public AbstractDatabaseEditForm
{
  Q_OBJECT

public:
  Q_INVOKABLE FirebirdProcedureForm();
  ~FirebirdProcedureForm();

  INJECT(SqlEditorSupport*, editorSupport);
  INJECT_AS(FirebirdTypeProvider*, typeProvider, firebirdTypeProvider)

private:
  Ui::FirebirdProcedureForm *ui;

  FirebirdProcedure* _procedureObj;
  ComboboxItemDelegate* _typesDelegate;

  // AbstractDatabaseEditForm interface
public:
  virtual void objectToForm() override;
  virtual void formToObject() override;
private slots:
  void on_btnApply_clicked();
  void on_btnClose_clicked();
  void on_btnAddInputArg_clicked();
  void on_btnDeleteInputArg_clicked();
  void on_btnAddOutputArg_clicked();
  void on_btnDeleteOutputArg_clicked();

  void onUserActionChanged();
};

#endif // FIREBIRDPROCEDUREFORM_H
