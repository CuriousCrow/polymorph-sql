#include "simplesequenceeditform.h"
#include "ui_simplesequenceeditform.h"
#include "objects/appconst.h"

SimpleSequenceEditForm::SimpleSequenceEditForm(QWidget *parent) :
    AbstractDatabaseEditForm(parent),
    ui(new Ui::SimpleSequenceEditForm)
{
    ui->setupUi(this);
}

SimpleSequenceEditForm::~SimpleSequenceEditForm()
{
    delete ui;
}

void SimpleSequenceEditForm::on_btnCancel_clicked()
{
    reject();
}

void SimpleSequenceEditForm::on_btnApply_clicked()
{
    tryUserAction();
}

void SimpleSequenceEditForm::objectToForm()
{
  ui->edtName->setText(_objItem->caption());
  ui->edtCurrentValue->setValue(_objItem->fieldValue(F_CURRENT_VALUE).toInt());
}

void SimpleSequenceEditForm::formToObject()
{
  _objItem->setFieldValue(F_CAPTION, ui->edtName->text());
  _objItem->setFieldValue(F_CURRENT_VALUE, ui->edtCurrentValue->value());
}
