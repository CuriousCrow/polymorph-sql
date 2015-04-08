#include "connectioneditdialog.h"
#include "ui_connectioneditdialog.h"
#include <QDebug>
#include <QFileDialog>

ConnectionEditDialog::ConnectionEditDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ConnectionEditDialog)
{
  ui->setupUi(this);
  on_cbServerType_activated(0);
  mapper = new QDataWidgetMapper(this);
  mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

ConnectionEditDialog::~ConnectionEditDialog()
{
  delete ui;
}

void ConnectionEditDialog::setModel(QSqlTableModel *sqlmodel)
{
  model = sqlmodel;
  mapper->setModel(model);
  mapper->addMapping(ui->edtDatabaseName, model->fieldIndex("NAME"));
  mapper->addMapping(ui->edtHostAddress, model->fieldIndex("HOST_ADDRESS"));
  mapper->addMapping(ui->edtLocalAddress, model->fieldIndex("LOCAL_PATH"));
  mapper->addMapping(ui->edtUserName, model->fieldIndex("USERNAME"));
  mapper->addMapping(ui->edtPassword, model->fieldIndex("PASSWORD"));
}

void ConnectionEditDialog::on_cbServerType_activated(int index)
{
  bool isLocalDatabase = index == 0;
  ui->lblLocalPath->setVisible(isLocalDatabase);
  ui->btnBrowseLocalAddress->setVisible(isLocalDatabase);
  ui->edtLocalAddress->setVisible(isLocalDatabase);
  ui->lblHostAddress->setVisible(!isLocalDatabase);
  ui->edtHostAddress->setVisible(!isLocalDatabase);
}

void ConnectionEditDialog::onDatabaseIndexChanged(QModelIndex idx)
{
  mapper->setCurrentModelIndex(idx);
}

void ConnectionEditDialog::on_btnOk_clicked()
{
  mapper->submit();
  model->submit();
  accept();
}

void ConnectionEditDialog::on_btnBrowseLocalAddress_clicked()
{
  QString localPath = QFileDialog::getOpenFileName(this);
  if (localPath.isEmpty())
    return;
  ui->edtLocalAddress->setText(localPath);
}
