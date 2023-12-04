#include "checkconstrainteditform.h"
#include "ui_checkconstrainteditform.h"
#include "objects/appconst.h"

CheckConstraintEditForm::CheckConstraintEditForm(QWidget *parent) :
  AbstractDatabaseEditForm(parent),
  ui(new Ui::CheckConstraintEditForm)
{
  ui->setupUi(this);
  connect(this, &CheckConstraintEditForm::userActionChanged,
          this, &CheckConstraintEditForm::onUserActionChanged);
}

CheckConstraintEditForm::~CheckConstraintEditForm()
{
  delete ui;
}

void CheckConstraintEditForm::on_btnApply_clicked()
{
  tryUserAction();
}

void CheckConstraintEditForm::on_btnCancel_clicked()
{
  reject();
}

void CheckConstraintEditForm::onUserActionChanged()
{
  ui->btnApply->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->edtName->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->edtExpression->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
}

void CheckConstraintEditForm::objectToForm()
{
  ui->edtName->setText(_objItem->caption());
  ui->edtExpression->setPlainText(_objItem->fieldValue(F_EXPRESSION).toString());
}

void CheckConstraintEditForm::formToObject()
{
  _objItem->setFieldValue(F_CAPTION, ui->edtName->text());
  _objItem->setFieldValue(F_EXPRESSION, ui->edtExpression->toPlainText());
}
