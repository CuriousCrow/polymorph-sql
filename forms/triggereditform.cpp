#include "triggereditform.h"
#include "ui_triggereditform.h"

TriggerEditForm::TriggerEditForm(QWidget *parent) :
  AbstractDatabaseEditForm(parent),
  ui(new Ui::TriggerEditForm)
{
  ui->setupUi(this);

  connect(this, SIGNAL(userActionChanged()), SLOT(onUserActionChanged()));
}

TriggerEditForm::~TriggerEditForm()
{
  delete ui;
}


void TriggerEditForm::objectToForm()
{
  ui->edtName->setText(_objItem->fieldValue(F_CAPTION).toString());
  ui->cmbBeforeAfter->setCurrentText(_objItem->fieldValue(F_TIMING).toString());
  ui->cmbFunction->setCurrentText(_objItem->fieldValue(F_FUNCTION).toString());
  ui->chkEnabled->setChecked(_objItem->fieldValue(F_ENABLED).toBool());
  ui->chkInsertEvent->setChecked(_objItem->fieldValue(F_EVENT_INSERT).toBool());
  ui->chkUpdateEvent->setChecked(_objItem->fieldValue(F_EVENT_UPDATE).toBool());
  ui->chkDeleteEvent->setChecked(_objItem->fieldValue(F_EVENT_DELETE).toBool());
  ui->chkTruncateEvent->setChecked(_objItem->fieldValue(F_EVENT_TRUNCATE).toBool());
}

void TriggerEditForm::formToObject()
{
  _objItem->setFieldValue(F_CAPTION, ui->edtName->text());
  _objItem->setFieldValue(F_ENABLED, ui->chkEnabled->isChecked());
}

void TriggerEditForm::on_btnApply_clicked()
{
  formToObject();
  accept();
}

void TriggerEditForm::on_btnCancel_clicked()
{
  reject();
}

void TriggerEditForm::onUserActionChanged()
{
  ui->cmbBeforeAfter->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->cmbFunction->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->chkInsertEvent->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->chkUpdateEvent->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->chkDeleteEvent->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->chkTruncateEvent->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
}
