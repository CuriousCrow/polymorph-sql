#include "procedureeditform.h"
#include "ui_procedureeditform.h"
#include <QTableView>
#include <QHeaderView>
#include "objects/appconst.h"
#include "widgets/lqueryeditor.h"

ProcedureEditForm::ProcedureEditForm() :
  AbstractDatabaseEditForm(nullptr),
  ui(new Ui::ProcedureEditForm)
{
  ui->setupUi(this);
  connect(this, SIGNAL(userActionChanged()), SLOT(onUserActionChanged()));
}

ProcedureEditForm::~ProcedureEditForm()
{
  delete ui;
}

void ProcedureEditForm::reloadTypes()
{
  QStringList types = _kb->typeNamesByDriver(_objItem->driverName());
  ui->cmbResultType->clear();
  ui->cmbResultType->addItem("void");
  ui->cmbResultType->addItem("trigger");
  ui->cmbResultType->addItems(types);
}

void ProcedureEditForm::objectToForm()
{
  _editorSupport->setEditor(ui->edtSourceCode);
  _editorSupport->updateModels(_objItem);

  reloadTypes();
  ui->edtName->setText(_objItem->caption());
  ui->edtSourceCode->setPlainText(_objItem->fieldValue(F_SOURCE_CODE).toString());
  ui->cmbLanguage->setCurrentText(_objItem->fieldValue(F_LANGUAGE).toString());
  ui->cmbResultType->setCurrentText(_objItem->fieldValue(F_RETURN_TYPE).toString());
}

void ProcedureEditForm::formToObject()
{
  _objItem->setFieldValue(F_CAPTION, ui->edtName->text());
  _objItem->setFieldValue(F_SOURCE_CODE, ui->edtSourceCode->toPlainText());
  _objItem->setFieldValue(F_LANGUAGE, ui->cmbLanguage->currentText());
  _objItem->setFieldValue(F_RETURN_TYPE, ui->cmbResultType->currentText());
}

void ProcedureEditForm::on_btnApply_clicked()
{
  tryUserAction();
}

void ProcedureEditForm::on_btnCancel_clicked()
{
  reject();
}

void ProcedureEditForm::onUserActionChanged()
{
  ui->edtName->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->cmbLanguage->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->cmbResultType->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
}
