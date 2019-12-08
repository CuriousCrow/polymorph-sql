#include "connectioneditdialog.h"
#include "ui_connectioneditdialog.h"
#include <QDebug>
#include <QFileDialog>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QStringListModel>
#include "core/core.h"

ConnectionEditDialog::ConnectionEditDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ConnectionEditDialog)
{
  ui->setupUi(this);
  _mapper = new LDataWidgetMapper(this);
  _mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

  QStringListModel* mModules = new QStringListModel(this);
  mModules->setStringList(Core::instance()->moduleNames());
  ui->cmbDriverName->setModel(mModules);
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
  _mapper->addMapping(ui->edtConnectionName, 0);
  _mapper->addMapping(ui->edtHostAddress, 2);
  _mapper->addMapping(ui->edtUserName, 3);
  _mapper->addMapping(ui->edtPassword, 4);
  _mapper->addMapping(ui->cmbDriverName, 5);
  _mapper->addMapping(ui->edtDatabaseName, 6);
}

LDataWidgetMapper *ConnectionEditDialog::mapper()
{
  return _mapper;
}

void ConnectionEditDialog::onDatabaseIndexChanged(QModelIndex idx)
{
  _mapper->setCurrentModelIndex(idx);
}

void ConnectionEditDialog::on_btnOk_clicked()
{  
  _mapper->submit();
  DBObjectItem* item = qobject_cast<DBObjectItem*>(_model->itemByIndex(_model->index(_mapper->currentIndex(),0, _mapper->rootIndex())));
  ActionResult res = item->updateMe();
  if (res.isSuccess()) {
    accept();
  }
  else {
    QMessageBox::warning(this, "Warning", "Error connecting database: " + res.description());
  }
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
  _mapper->revert();
  reject();
}
