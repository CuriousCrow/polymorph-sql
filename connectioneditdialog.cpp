#include "connectioneditdialog.h"
#include "ui_connectioneditdialog.h"
#include <QDebug>
#include <QFileDialog>
#include "qsqlqueryhelper.h"
#include "qdbdatabaseitem.h"

ConnectionEditDialog::ConnectionEditDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ConnectionEditDialog)
{
  ui->setupUi(this);
  on_cbServerType_activated(0);
  _mapper = new LDataWidgetMapper(this);
  _mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

ConnectionEditDialog::~ConnectionEditDialog()
{
  delete ui;
}

void ConnectionEditDialog::setModel(QStructureItemModel *model)
{
  _model = model;
  _mapper->setModel(_model);
  _mapper->setRootIndex(QModelIndex());
  _mapper->addMapping(ui->edtDatabaseName, 0);
  _mapper->addMapping(ui->edtHostAddress, 1);
  _mapper->addMapping(ui->edtUserName, 2);
  _mapper->addMapping(ui->edtPassword, 3);
  _mapper->addMapping(ui->edtLocalAddress, 4);
  _mapper->addMapping(ui->cmbDriverName, 5);
}

LDataWidgetMapper *ConnectionEditDialog::mapper()
{
  return _mapper;
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
  _mapper->setCurrentModelIndex(idx);
}

void ConnectionEditDialog::on_btnOk_clicked()
{  
  _mapper->submit();
  QDBObjectItem* item = (QDBObjectItem*)_model->itemByIndex(_model->index(_mapper->currentIndex(),0, _mapper->rootIndex()));
  if (item->updateMe())
    accept();
}

void ConnectionEditDialog::on_btnBrowseLocalAddress_clicked()
{
  QString localPath = QFileDialog::getOpenFileName(this);
  if (localPath.isEmpty())
    return;
  ui->edtLocalAddress->setText(localPath);
}

void ConnectionEditDialog::on_btnTryToConnect_clicked()
{

}

void ConnectionEditDialog::on_btnCancel_clicked()
{
  _mapper->revert();
  reject();
}
