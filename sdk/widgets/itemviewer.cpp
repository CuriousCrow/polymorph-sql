#include "itemviewer.h"
#include "ui_itemviewer.h"

ItemViewer::ItemViewer(QWidget *parent) :
  QStackedWidget(parent),
  ui(new Ui::ItemViewer)
{
  ui->setupUi(this);
}

ItemViewer::~ItemViewer()
{
  delete ui;
}

void ItemViewer::setValue(QVariant value)
{
  _itemValue = value;
  ui->lblText->setText(_itemValue.toString());
  if (_itemValue.typeId() == QMetaType::QByteArray) {
    QPixmap pic;
    pic.loadFromData(_itemValue.toByteArray());
    ui->lblImage->setPixmap(pic);
  }
  setTypeByValue();
}

void ItemViewer::setTypeByValue()
{
  if (_itemValue.typeId() == QMetaType::QByteArray) {
    setCurrentIndex(EditorType::Image);
  }
  else {
    setCurrentIndex(EditorType::Text);
  }
}
