#include "tableeditform.h"
#include "ui_tableeditform.h"
#include <QMessageBox>

TableEditForm::TableEditForm(QWidget *parent) :
  AbstractDatabaseEditForm(parent),
  ui(new Ui::TableEditForm)
{
  ui->setupUi(this);
  _colTypeDelegate = new ComboboxHashDelegate(ui->tableView);
  ui->tableView->setItemDelegateForColumn(COL_IDX_TYPE, _colTypeDelegate);
}

TableEditForm::~TableEditForm()
{
  delete ui;
}

void TableEditForm::objectToForm()
{
  QString tableName = _objItem->fieldValue("caption").toString();
  setWindowTitle("Редактор таблицы " + tableName);
  ui->lineEdit->setText(tableName);
  QDBTableItem* tableItem = qobject_cast<QDBTableItem*>(_objItem);
  tableItem->reloadColumnsModel();
  _colTypeDelegate->setItemsHash(tableItem->getColumnTypesHash());
  ui->tableView->setModel(tableItem->columnsModel());
}

void TableEditForm::formToObject()
{
  _objItem->setFieldValue("caption", ui->lineEdit->text());
  //Модель автоматически обновится при редактировании
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

void TableEditForm::on_btnAdd_clicked()
{
  qobject_cast<QDBTableItem*>(_objItem)->addDefaultColumn();
}

void TableEditForm::on_btnDelete_clicked()
{
  int selectedRow = ui->tableView->currentIndex().row();
  if (selectedRow >= 0) {
    qobject_cast<QDBTableItem*>(_objItem)->columnsModel()->removeRow(selectedRow);
  }
  else {
    QMessageBox::warning(this, trUtf8("Warning"), "Please, select the column you want to drop");
  }
}
