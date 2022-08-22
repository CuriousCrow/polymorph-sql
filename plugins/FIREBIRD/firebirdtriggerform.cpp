#include "firebirdtriggerform.h"
#include "ui_firebirdtriggerform.h"
#include "objects/appconst.h"

FirebirdTriggerForm::FirebirdTriggerForm() :
  AbstractDatabaseEditForm(),
  ui(new Ui::FirebirdTriggerForm)
{
  ui->setupUi(this);

  connect(this, SIGNAL(userActionChanged()), SLOT(onUserActionChanged()));
}

FirebirdTriggerForm::~FirebirdTriggerForm()
{
  delete ui;
}

void FirebirdTriggerForm::objectToForm()
{
  ui->cmbTargetTable->setModel(_ds->structureModel());
  ui->cmbTargetTable->setRootModelIndex(_ds->itemIdx(_objItem, FOLDER_TABLES));

  ui->edtName->setText(_objItem->caption());
  if (userAction() == AbstractDatabaseEditForm::Edit) {
    ui->cmbBeforeAfter->setCurrentText(_objItem->fieldValue(F_TIMING).toString());
    ui->teCodeBlock->setPlainText(_objItem->fieldValue(F_FUNCTION).toString());
    ui->cmbTargetTable->setCurrentText(_objItem->fieldValue(F_TABLE).toString());
    ui->chkInsertEvent->setChecked(_objItem->fieldValue(F_EVENT_INSERT).toBool());
    ui->chkUpdateEvent->setChecked(_objItem->fieldValue(F_EVENT_UPDATE).toBool());
    ui->chkDeleteEvent->setChecked(_objItem->fieldValue(F_EVENT_DELETE).toBool());
  }

  if (userAction() == AbstractDatabaseEditForm::Create) {
    ui->cmbTargetTable->setCurrentIndex(0);
  }
}

void FirebirdTriggerForm::formToObject()
{
  _objItem->setFieldValue(F_CAPTION, ui->edtName->text());
  _objItem->setFieldValue(F_TIMING, ui->cmbBeforeAfter->currentText());
  _objItem->setFieldValue(F_FUNCTION, ui->teCodeBlock->toPlainText());
  _objItem->setFieldValue(F_TABLE, ui->cmbTargetTable->currentText());
  _objItem->setFieldValue(F_EVENT_INSERT, ui->chkInsertEvent->isChecked());
  _objItem->setFieldValue(F_EVENT_UPDATE, ui->chkUpdateEvent->isChecked());
  _objItem->setFieldValue(F_EVENT_DELETE, ui->chkDeleteEvent->isChecked());
}

void FirebirdTriggerForm::on_btnApply_clicked()
{
  tryUserAction();
}

void FirebirdTriggerForm::on_btnCancel_clicked()
{
  cancel();
}

void FirebirdTriggerForm::onUserActionChanged()
{
  ui->edtName->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->cmbBeforeAfter->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->teCodeBlock->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->cmbTargetTable->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->chkInsertEvent->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->chkUpdateEvent->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->chkDeleteEvent->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->btnApply->setEnabled(userAction() == UserAction::Create);
  ui->btnCancel->setText(userAction() == UserAction::Create ? tr("Cancel") : tr("Close"));
}
