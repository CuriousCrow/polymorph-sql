#include "databaseexportform.h"
#include "ui_databaseexportform.h"

DatabaseExportForm::DatabaseExportForm(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DatabaseExportForm)
{
  ui->setupUi(this);
}

DatabaseExportForm::~DatabaseExportForm()
{
  delete ui;
}
