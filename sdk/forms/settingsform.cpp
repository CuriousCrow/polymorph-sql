#include "settingsform.h"
#include "ui_settingsform.h"

SettingsForm* SettingsForm::_singleton = nullptr;

SettingsForm::SettingsForm(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SettingsForm)
{
  ui->setupUi(this);
}

SettingsForm::~SettingsForm()
{
  delete ui;
}

SettingsForm *SettingsForm::instance()
{
  if (!_singleton) {
    _singleton = new SettingsForm();
  }
  return _singleton;
}

void SettingsForm::on_btnClose_clicked()
{
  close();
}
