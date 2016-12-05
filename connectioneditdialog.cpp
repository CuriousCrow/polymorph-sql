#include "connectioneditdialog.h"
#include "ui_connectioneditdialog.h"
#include <QDebug>
#include <QFileDialog>
#include <QSqlDatabase>

ConnectionEditDialog::ConnectionEditDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ConnectionEditDialog)
{
  ui->setupUi(this);
  _mapper = new LDataWidgetMapper(this);
  _mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

  removeUnavailableDriversFromCombobox();
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
  _mapper->addMapping(ui->edtHostAddress, 1);
  _mapper->addMapping(ui->edtUserName, 2);
  _mapper->addMapping(ui->edtPassword, 3);
  _mapper->addMapping(ui->cmbDriverName, 5);
  _mapper->addMapping(ui->edtDatabaseName, 4);
}

LDataWidgetMapper *ConnectionEditDialog::mapper()
{
  return _mapper;
}

void ConnectionEditDialog::onDatabaseIndexChanged(QModelIndex idx)
{
  _mapper->setCurrentModelIndex(idx);
}

void ConnectionEditDialog::removeUnavailableDriversFromCombobox()
{
  QStringList availableDrivers = QSqlDatabase::drivers();
  for (int i = ui->cmbDriverName->count() - 1; i >= 0; i--){
    if (!availableDrivers.contains(ui->cmbDriverName->itemText(i)))
      ui->cmbDriverName->removeItem(i);
  }
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
