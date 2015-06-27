#include "vieweditdialog.h"
#include "ui_vieweditdialog.h"

ViewEditDialog::ViewEditDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ViewEditDialog)
{
  ui->setupUi(this);
  _mapper = new QDataWidgetMapper(this);
  _mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

ViewEditDialog::~ViewEditDialog()
{
  delete ui;
}

void ViewEditDialog::setModel(QAbstractItemModel *model)
{
  _mapper->setModel(model);
  _mapper->addMapping(ui->edtName, 0);
  _mapper->addMapping(ui->edtQueryText, 1);
}

void ViewEditDialog::onModelIndexChanged(QModelIndex index)
{
  _mapper->setRootIndex(index.parent());
  _mapper->setCurrentModelIndex(index);
}

void ViewEditDialog::on_btnOk_clicked()
{
  _mapper->submit();
  accept();
}

void ViewEditDialog::on_btnCancel_clicked()
{
  _mapper->revert();
  reject();
}
