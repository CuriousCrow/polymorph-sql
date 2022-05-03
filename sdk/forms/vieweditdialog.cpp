#include "vieweditdialog.h"
#include "ui_vieweditdialog.h"
#include "../objects/appconst.h"
#include <QMessageBox>
#include <QDebug>
#include <QTableView>
#include <QHeaderView>

ViewEditDialog::ViewEditDialog() :
  AbstractDatabaseEditForm(nullptr),
  ui(new Ui::ViewEditDialog)
{
  ui->setupUi(this);
  connect(this, SIGNAL(userActionChanged()), SLOT(onUserActionChanged()));
}

ViewEditDialog::~ViewEditDialog()
{
  delete ui;
}

void ViewEditDialog::inject_sqlCompleterSupport_into_form(SimpleSqlCompleterSupport *completerSupport)
{
  completerSupport->setParent(this);
  _completerSupport = completerSupport;
  _completerSupport->setWidget(ui->edtQueryText);
}

void ViewEditDialog::on_btnOk_clicked()
{
  tryUserAction();
}

void ViewEditDialog::on_btnCancel_clicked()
{
  if (userAction() == AbstractDatabaseEditForm::Create) {
    delete  _objItem;
  }
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
  _completerSupport->setItem(_objItem);

  ui->edtName->setText(_objItem->caption());
  ui->edtQueryText->setPlainText(_objItem->fieldValue(F_QUERY_TEXT).toString());
}

void ViewEditDialog::formToObject()
{
  _objItem->setFieldValue(F_CAPTION, ui->edtName->text());
  _objItem->setFieldValue(F_QUERY_TEXT, ui->edtQueryText->toPlainText());
}

void ViewEditDialog::localEvent(LocalEvent *event)
{
  qDebug() << "View edit dialog event:" << event->type();
}
