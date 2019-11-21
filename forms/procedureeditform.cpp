#include "procedureeditform.h"
#include "ui_procedureeditform.h"

#include "../dbms/appconst.h"

ProcedureEditForm::ProcedureEditForm(QWidget *parent) :
  AbstractDatabaseEditForm(parent),
  ui(new Ui::ProcedureEditForm)
{
  ui->setupUi(this);
}

ProcedureEditForm::~ProcedureEditForm()
{
  delete ui;
}

void ProcedureEditForm::objectToForm()
{
  ui->edtName->setText(_objItem->fieldValue(F_CAPTION).toString());
  ui->edtSourceCode->setPlainText(_objItem->fieldValue(F_SOURCE_CODE).toString());
}

void ProcedureEditForm::formToObject()
{
  _objItem->setFieldValue(F_CAPTION, ui->edtName->text());
  _objItem->setFieldValue(F_SOURCE_CODE, ui->edtSourceCode->toPlainText());
}

void ProcedureEditForm::on_btnApply_clicked()
{
  formToObject();
  accept();
}

void ProcedureEditForm::on_btnCancel_clicked()
{
  reject();
}
