#include "connectioneditdialog.h"
#include "ui_connectioneditdialog.h"
#include <QDebug>
#include <QFileDialog>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QStringListModel>
#include "../core/core.h"
#include "../objects/appconst.h"

ConnectionEditDialog::ConnectionEditDialog(QWidget *parent) :
  AbstractDatabaseEditForm(parent),
  ui(new Ui::ConnectionEditDialog)
{
  ui->setupUi(this);

  QStringListModel* mModules = new QStringListModel(this);
  mModules->setStringList(Core::instance()->supportedDrivers());
  ui->cmbDriverName->setModel(mModules);

  connect(this, SIGNAL(userActionChanged()),
          SLOT(onUserActionChanged()));
}

ConnectionEditDialog::~ConnectionEditDialog()
{
  delete ui;
}

void ConnectionEditDialog::on_btnOk_clicked()
{  
  tryUserAction();
}

void ConnectionEditDialog::on_btnBrowseLocalAddress_clicked()
{
  QString localPath = QFileDialog::getOpenFileName(this);
  if (localPath.isEmpty())
    return;
  ui->edtDatabaseName->setText(localPath);
}

void ConnectionEditDialog::on_btnTryToConnect_clicked()
{

}

void ConnectionEditDialog::on_btnCancel_clicked()
{
  reject();
}


void ConnectionEditDialog::objectToForm()
{
  ui->edtConnectionName->setText(_objItem->caption());
  ui->edtUserName->setText(_objItem->fieldValue(F_USERNAME).toString());
  ui->edtPassword->setText(_objItem->fieldValue(F_PASSWORD).toString());
  ui->edtHostAddress->setText(_objItem->fieldValue(F_HOSTNAME).toString());
  ui->cmbDriverName->setCurrentText(_objItem->fieldValue(F_DRIVER_NAME).toString());
  ui->edtDatabaseName->setText(_objItem->fieldValue(F_DATABASE_NAME).toString());
}

void ConnectionEditDialog::formToObject()
{
  _objItem->setFieldValue(F_CAPTION, ui->edtConnectionName->text());
  _objItem->setFieldValue(F_USERNAME, ui->edtUserName->text());
  _objItem->setFieldValue(F_PASSWORD, ui->edtPassword->text());
  _objItem->setFieldValue(F_HOSTNAME, ui->edtHostAddress->text());
  _objItem->setFieldValue(F_DRIVER_NAME, ui->cmbDriverName->currentText());
  _objItem->setFieldValue(F_DATABASE_NAME, ui->edtDatabaseName->text());
}

void ConnectionEditDialog::on_btnCreate_clicked()
{
  formToObject();
  DBDatabaseItem* dbItem = static_cast<DBDatabaseItem*>(_objItem);
  ActionResult res = dbItem->createDatabase();
  if (res.isSuccess())
    QMessageBox::information(this, "Information", "Database successfully created");
  else
    QMessageBox::critical(this, "Error", res.description());
}

void ConnectionEditDialog::on_btnDrop_clicked()
{
  formToObject();
  DBDatabaseItem* dbItem = static_cast<DBDatabaseItem*>(_objItem);
  ActionResult res = dbItem->dropDatabase();
  if (res.isSuccess())
    QMessageBox::information(this, "Information", "Database successfully dropped");
  else
    QMessageBox::critical(this, "Error", res.description());
}

void ConnectionEditDialog::onUserActionChanged()
{
  ui->btnDrop->setEnabled(userAction() != AbstractDatabaseEditForm::Create);
}
