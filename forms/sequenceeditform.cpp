#include "sequenceeditform.h"
#include "ui_sequenceeditform.h"
#include "dbms/appconst.h"

SequenceEditForm::SequenceEditForm(QWidget *parent) :
  AbstractDatabaseEditForm(parent),
  ui(new Ui::SequenceEditForm)
{
  ui->setupUi(this);
}

SequenceEditForm::~SequenceEditForm()
{
  delete ui;
}

void SequenceEditForm::on_btnApply_clicked()
{
  formToObject();
  accept();
}

void SequenceEditForm::on_btnCancel_clicked()
{
  reject();
}

void SequenceEditForm::objectToForm()
{
  ui->edtName->setText(_objItem->fieldValue(F_CAPTION).toString());
  ui->edtCurrentValue->setValue(_objItem->fieldValue(F_CURRENT_VALUE).toInt());
}

void SequenceEditForm::formToObject()
{

}
