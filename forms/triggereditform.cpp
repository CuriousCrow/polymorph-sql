#include "triggereditform.h"
#include "ui_triggereditform.h"

TriggerEditForm::TriggerEditForm(QWidget *parent) :
  AbstractDatabaseEditForm(parent),
  ui(new Ui::TriggerEditForm)
{
  ui->setupUi(this);
}

TriggerEditForm::~TriggerEditForm()
{
  delete ui;
}


void TriggerEditForm::objectToForm()
{
  ui->edtName->setText(_objItem->fieldValue(F_CAPTION).toString());
}

void TriggerEditForm::formToObject()
{
  _objItem->setFieldValue(F_CAPTION, ui->edtName->text());
}

void TriggerEditForm::on_btnApply_clicked()
{
  formToObject();
  accept();
}

void TriggerEditForm::on_btnCaption_clicked()
{
  reject();
}
