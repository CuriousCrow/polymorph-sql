#include "tableeditform.h"
#include "ui_tableeditform.h"

TableEditForm::TableEditForm(QWidget *parent) :
    AbstractDatabaseEditForm(parent),
    ui(new Ui::TableEditForm)
{
    ui->setupUi(this);
    _rowsModel = new TableRowModel(this);
    ui->tableView->setModel(_rowsModel);
}

TableEditForm::~TableEditForm()
{
    delete ui;
}

void TableEditForm::objectToForm()
{
    ui->lineEdit->setText(_objItem->fieldValue("caption").toString());
    _rowsModel->setTableItem(_objItem);
}

void TableEditForm::formToObject()
{
    _objItem->setFieldValue("caption", ui->lineEdit->text());
}

void TableEditForm::on_pushButton_clicked()
{
  formToObject();
  accept();
}

void TableEditForm::on_pushButton_2_clicked()
{
  reject();
}


