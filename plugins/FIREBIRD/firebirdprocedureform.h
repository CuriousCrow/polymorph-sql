#ifndef FIREBIRDPROCEDUREFORM_H
#define FIREBIRDPROCEDUREFORM_H

#include "forms/abstractdatabaseitemform.h"
#include "tools/sqleditorsupport.h"
#include "firebirdprocedure.h"
#include "firebirdtypeprovider.h"


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

private:
  Ui::FirebirdProcedureForm *ui;

  FirebirdTypeProvider* _typeProvider;
  FirebirdProcedure* _procedureObj;

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
