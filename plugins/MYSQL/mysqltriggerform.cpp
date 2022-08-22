#include "mysqltriggerform.h"
#include "ui_mysqltriggerform.h"
#include "objects/appconst.h"

MysqlTriggerForm::MysqlTriggerForm() :
  AbstractDatabaseEditForm(),
  ui(new Ui::MysqlTriggerForm)
{
  ui->setupUi(this);

  connect(this, SIGNAL(userActionChanged()), SLOT(onUserActionChanged()));
}

MysqlTriggerForm::~MysqlTriggerForm()
{
  delete ui;
}

void MysqlTriggerForm::objectToForm()
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
    ui->chkTruncateEvent->setChecked(_objItem->fieldValue(F_EVENT_TRUNCATE).toBool());
  }

  if (userAction() == AbstractDatabaseEditForm::Create) {
    ui->cmbTargetTable->setCurrentIndex(0);
  }
}

void MysqlTriggerForm::formToObject()
{
  _objItem->setFieldValue(F_CAPTION, ui->edtName->text());
  _objItem->setFieldValue(F_TIMING, ui->cmbBeforeAfter->currentText());
  _objItem->setFieldValue(F_FUNCTION, ui->teCodeBlock->toPlainText());
  _objItem->setFieldValue(F_TABLE, ui->cmbTargetTable->currentText());
  _objItem->setFieldValue(F_EVENT_INSERT, ui->chkInsertEvent->isChecked());
  _objItem->setFieldValue(F_EVENT_UPDATE, ui->chkUpdateEvent->isChecked());
  _objItem->setFieldValue(F_EVENT_DELETE, ui->chkDeleteEvent->isChecked());
  _objItem->setFieldValue(F_EVENT_TRUNCATE, ui->chkTruncateEvent->isChecked());
}

void MysqlTriggerForm::on_btnApply_clicked()
{
  tryUserAction();
}

void MysqlTriggerForm::on_btnCancel_clicked()
{
  cancel();
}

void MysqlTriggerForm::onUserActionChanged()
{
  ui->edtName->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->cmbBeforeAfter->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->teCodeBlock->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->cmbTargetTable->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->chkInsertEvent->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->chkUpdateEvent->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->chkDeleteEvent->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->chkTruncateEvent->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->btnApply->setEnabled(userAction() == UserAction::Create);
  ui->btnCancel->setText(userAction() == UserAction::Create ? tr("Cancel") : tr("Close"));
}

void MysqlTriggerForm::on_edtName_textChanged(const QString &text)
{
  setWindowTitle("Trigger: " + text);
}
