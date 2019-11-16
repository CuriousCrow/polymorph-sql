#include "vieweditdialog.h"
#include "ui_vieweditdialog.h"
#include "../dbms/appconst.h"

ViewEditDialog::ViewEditDialog(QWidget *parent) :
  AbstractDatabaseEditForm(parent),
  ui(new Ui::ViewEditDialog)
{
  ui->setupUi(this);

  connect(this, SIGNAL(userActionChanged()), SLOT(onUserActionChanged()));
}

ViewEditDialog::~ViewEditDialog()
{
  delete ui;
}

void ViewEditDialog::on_btnOk_clicked()
{
  formToObject();
  accept();
}

void ViewEditDialog::on_btnCancel_clicked()
{
  reject();
}

void ViewEditDialog::onUserActionChanged()
{
  ui->edtName->setReadOnly(userAction() != UserAction::Create);
  ui->edtQueryText->setReadOnly(userAction() != UserAction::Create);
  ui->btnOk->setEnabled(userAction() == UserAction::Create);
  ui->btnCancel->setText(userAction() == UserAction::Create ? tr("Cancel") : tr("Close"));
}

void ViewEditDialog::objectToForm()
{
  ui->edtName->setText(_objItem->fieldValue(F_CAPTION).toString());
  ui->edtQueryText->setPlainText(_objItem->fieldValue(F_QUERY_TEXT).toString());
}

void ViewEditDialog::formToObject()
{
  _objItem->setFieldValue(F_CAPTION, ui->edtName->text());
  _objItem->setFieldValue(F_QUERY_TEXT, ui->edtQueryText->toPlainText());
}
