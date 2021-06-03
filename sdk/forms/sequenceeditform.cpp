#include "sequenceeditform.h"
#include "ui_sequenceeditform.h"
#include "../objects/appconst.h"
#include <QDebug>

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
  tryUserAction();
}

void SequenceEditForm::on_btnCancel_clicked()
{
  reject();
}

void SequenceEditForm::objectToForm()
{
  ui->edtName->setText(_objItem->caption());
  ui->edtCurrentValue->setValue(_objItem->fieldValue(F_CURRENT_VALUE).toInt());
  ui->edtMinValue->setValue(_objItem->fieldValue(F_MIN_VALUE).toInt());
  ui->edtMaxValue->setValue(_objItem->fieldValue(F_MAX_VALUE).toInt());
  ui->edtStartValue->setValue(_objItem->fieldValue(F_START_VALUE).toInt());
  ui->edtStep->setValue(_objItem->fieldValue(F_STEP).toInt());
}

void SequenceEditForm::formToObject()
{
  _objItem->setFieldValue(F_CAPTION, ui->edtName->text());
  _objItem->setFieldValue(F_CURRENT_VALUE, ui->edtCurrentValue->value());
  _objItem->setFieldValue(F_MIN_VALUE, ui->edtMinValue->value());
  _objItem->setFieldValue(F_MAX_VALUE, ui->edtMaxValue->value());
  _objItem->setFieldValue(F_START_VALUE, ui->edtStartValue->value());
  _objItem->setFieldValue(F_STEP, ui->edtStep->value());
}

