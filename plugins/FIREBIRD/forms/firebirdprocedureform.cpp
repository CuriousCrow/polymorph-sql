#include "firebirdprocedureform.h"
#include "ui_firebirdprocedureform.h"
#include "objects/appconst.h"


FirebirdProcedureForm::FirebirdProcedureForm() :
  AbstractDatabaseEditForm(),
  ui(new Ui::FirebirdProcedureForm)
{
  ui->setupUi(this);

  _typesDelegate = new ComboboxItemDelegate(this);
  connect(this, SIGNAL(userActionChanged()), SLOT(onUserActionChanged()));
}

FirebirdProcedureForm::~FirebirdProcedureForm()
{
  delete ui;
}

void FirebirdProcedureForm::objectToForm()
{
  _editorSupport->setEditor(ui->teSource);
  _editorSupport->updateModels(_objItem);

  _typeProvider->setItemObject(_objItem);

  _typesDelegate->setOptions(_typeProvider->typeNames());
  ui->tvInputArguments->setItemDelegateForColumn(1, _typesDelegate);
  ui->tvOutputArguments->setItemDelegateForColumn(1, _typesDelegate);

  _procedureObj = static_cast<FirebirdProcedure*>(_objItem);
  ui->tvInputArguments->setModel(_procedureObj->inArgumentModel());
  ui->tvOutputArguments->setModel(_procedureObj->outArgumentModel());

  ui->edtName->setText(_objItem->caption());
  QString sourceCode = _objItem->fieldValue(F_SOURCE_CODE).toString();
  if (sourceCode.isEmpty())
    sourceCode = "BEGIN\nEND";
  ui->teSource->setPlainText(sourceCode);
}

void FirebirdProcedureForm::formToObject()
{
  _objItem->setFieldValue(F_CAPTION, ui->edtName->text());
  _objItem->setFieldValue(F_SOURCE_CODE, ui->teSource->toPlainText());
}

void FirebirdProcedureForm::on_btnApply_clicked()
{
  tryUserAction();
}

void FirebirdProcedureForm::on_btnClose_clicked()
{
  cancel();
}

void FirebirdProcedureForm::on_btnAddInputArg_clicked()
{
  _procedureObj->addInArg();
}

void FirebirdProcedureForm::on_btnDeleteInputArg_clicked()
{
  int row = ui->tvInputArguments->currentIndex().row();
  if (row < 0)
    return;
  _procedureObj->removeInArg(row);
}

void FirebirdProcedureForm::on_btnAddOutputArg_clicked()
{
  _procedureObj->addOutArg();
}

void FirebirdProcedureForm::on_btnDeleteOutputArg_clicked()
{
  int row = ui->tvOutputArguments->currentIndex().row();
  if (row < 0)
    return;
  _procedureObj->removeOutArg(row);
}
