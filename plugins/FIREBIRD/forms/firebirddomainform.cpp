#include "firebirddomainform.h"
#include "ui_firebirddomainform.h"
#include "objects/appconst.h"

FirebirdDomainForm::FirebirdDomainForm() :
  AbstractDatabaseEditForm(),
  ui(new Ui::FirebirdDomainForm)
{
  ui->setupUi(this);
}

FirebirdDomainForm::~FirebirdDomainForm()
{
  delete ui;
}

void FirebirdDomainForm::objectToForm()
{
  _typeProvider->setItemObject(_objItem);

  ui->cmbType->clear();
  ui->cmbType->addItems(_typeProvider->typeNames());

  ui->edtName->setText(_objItem->fieldValue(F_CAPTION).toString());
  ui->edtLength->setValue(_objItem->fieldValue(F_LENGTH).toInt());
  ui->edtDefault->setText(_objItem->fieldValue(F_DEFAULT).toString());
  ui->cmbType->setCurrentText(_objItem->fieldValue(F_TYPE).toString());
}

void FirebirdDomainForm::formToObject()
{
  _objItem->setFieldValue(F_CAPTION, ui->edtName->text());
  if (ui->edtLength->value() == 0)
    _objItem->setFieldValue(F_LENGTH, QVariant());
  else
    _objItem->setFieldValue(F_LENGTH, ui->edtLength->value());
  _objItem->setFieldValue(F_DEFAULT, ui->edtDefault->text());
  _objItem->setFieldValue(F_TYPE, ui->cmbType->currentText());
}

void FirebirdDomainForm::on_btnCancel_clicked()
{
  cancel();
}

void FirebirdDomainForm::on_btnApply_clicked()
{
  tryUserAction();
}

void FirebirdDomainForm::on_cmbType_currentTextChanged(const QString &type)
{
  DBType* typeInfo = _typeProvider->type(type);
  if (!typeInfo->hasLength()) {
    ui->edtLength->clear();
  }
  ui->edtLength->setEnabled(typeInfo->hasLength());
}
