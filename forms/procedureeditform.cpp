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
}

void ProcedureEditForm::formToObject()
{

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
