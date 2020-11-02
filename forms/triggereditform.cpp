#include "triggereditform.h"
#include "ui_triggereditform.h"
#include "../qstructureitemmodel.h"
#include "../core/datastore.h"

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
  ui->cmbTargetTable->setModel(DataStore::structureModel());
  ui->cmbTargetTable->setRootModelIndex(DataStore::itemIdx(_objItem, FOLDER_TABLES));

  ui->cmbFunction->setModel(DataStore::structureModel());
  ui->cmbFunction->setRootModelIndex(DataStore::itemIdx(_objItem, FOLDER_PROCEDURES));

  ui->edtName->setText(_objItem->caption());
  if (userAction() == AbstractDatabaseEditForm::Edit) {
    ui->cmbBeforeAfter->setCurrentText(_objItem->fieldValue(F_TIMING).toString());
    ui->cmbFunction->setCurrentText(_objItem->fieldValue(F_FUNCTION).toString());
    ui->cmbTargetTable->setCurrentText(_objItem->fieldValue(F_TABLE).toString());
    ui->chkEnabled->setChecked(_objItem->fieldValue(F_ENABLED).toBool());
    ui->chkInsertEvent->setChecked(_objItem->fieldValue(F_EVENT_INSERT).toBool());
    ui->chkUpdateEvent->setChecked(_objItem->fieldValue(F_EVENT_UPDATE).toBool());
    ui->chkDeleteEvent->setChecked(_objItem->fieldValue(F_EVENT_DELETE).toBool());
    ui->chkTruncateEvent->setChecked(_objItem->fieldValue(F_EVENT_TRUNCATE).toBool());
  }

  if (userAction() == AbstractDatabaseEditForm::Create) {
    ui->cmbFunction->setCurrentIndex(0);
    ui->cmbTargetTable->setCurrentIndex(0);
  }
}

void TriggerEditForm::formToObject()
{ 
  _objItem->setFieldValue(F_CAPTION, ui->edtName->text());
  _objItem->setFieldValue(F_ENABLED, ui->chkEnabled->isChecked());
  _objItem->setFieldValue(F_TIMING, ui->cmbBeforeAfter->currentText());
  _objItem->setFieldValue(F_FUNCTION, ui->cmbFunction->currentText() + "()");
  _objItem->setFieldValue(F_TABLE, ui->cmbTargetTable->currentText());
  _objItem->setFieldValue(F_EVENT_INSERT, ui->chkInsertEvent->isChecked());
  _objItem->setFieldValue(F_EVENT_UPDATE, ui->chkUpdateEvent->isChecked());
  _objItem->setFieldValue(F_EVENT_DELETE, ui->chkDeleteEvent->isChecked());
  _objItem->setFieldValue(F_EVENT_TRUNCATE, ui->chkTruncateEvent->isChecked());
}

void TriggerEditForm::on_btnApply_clicked()
{
  tryUserAction();
}

void TriggerEditForm::on_btnCancel_clicked()
{
  reject();
}

void TriggerEditForm::onUserActionChanged()
{
  ui->chkEnabled->setEnabled(userAction() == AbstractDatabaseEditForm::Edit);
  ui->cmbBeforeAfter->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->cmbFunction->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->cmbTargetTable->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->chkInsertEvent->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->chkUpdateEvent->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->chkDeleteEvent->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->chkTruncateEvent->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
}
