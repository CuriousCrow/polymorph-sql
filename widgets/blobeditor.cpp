#include "blobeditor.h"
#include "ui_blobeditor.h"

BlobEditor::BlobEditor(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::BlobEditor)
{
  ui->setupUi(this);
}

BlobEditor::~BlobEditor()
{
  delete ui;
}

void BlobEditor::setData(QByteArray data)
{
  _data = data;

  //Loading as text
  ui->edtPlainText->setPlainText(QString::fromUtf8(data));

  //Loading as picture
  QPixmap pic;
  pic.loadFromData(data);
  ui->lblImage->setPixmap(pic);
}

QByteArray BlobEditor::data()
{
  return _data;
}


void BlobEditor::on_btnClose_clicked()
{
  reject();
}

void BlobEditor::on_btnApply_clicked()
{
  _data = ui->edtPlainText->toPlainText().toUtf8();
  accept();
}

