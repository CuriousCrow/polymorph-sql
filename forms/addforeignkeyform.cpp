#include "addforeignkeyform.h"
#include "ui_addforeignkeyform.h"
#include <QDebug>
#include "dbms/appconst.h"
#include "core/datastore.h"


AddForeignKeyForm::AddForeignKeyForm(QWidget *parent) :
  AbstractDatabaseEditForm(parent),
  ui(new Ui::AddForeignKeyForm)
{
  ui->setupUi(this);
}

AddForeignKeyForm::~AddForeignKeyForm()
{
  qDebug() << "Add foreign key destructor";
  delete ui;
}

void AddForeignKeyForm::objectToForm()
{
  QStructureItemModel* structModel = DataStore::structureModel();
  QModelIndex idx = structModel->indexByName("qpsql://ughistory/tables");
  ui->cmbReferenceTable->setModel(structModel);
  ui->cmbReferenceTable->setRootModelIndex(idx);

  DBTableItem* targetObj = qobject_cast<DBTableItem*>(structModel->itemByName("qpsql://ughistory/tables/" + _objItem->fieldValue(F_TABLE).toString()));
  ui->cmbTargetColumn->setModel(targetObj->columnsModel());
  ui->cmbTargetColumn->setModelColumn(1);

  ui->edtName->setText(_objItem->fieldValue(F_CAPTION).toString());

  _objItem->submit();
}

void AddForeignKeyForm::formToObject()
{
  _objItem->setFieldValue(F_CAPTION, ui->edtName->text());
  _objItem->setFieldValue(F_COLUMN, ui->cmbTargetColumn->currentText());
  _objItem->setFieldValue(F_REFTABLE, ui->cmbReferenceTable->currentText());
  _objItem->setFieldValue(F_REFCOLUMN, ui->cmbReferenceColumn->currentText());
  _objItem->setFieldValue(F_ON_UPDATE, ui->cmbOnUpdateAction->currentText());
  _objItem->setFieldValue(F_ON_DELETE, ui->cmbOnDeleteAction->currentText());
}

void AddForeignKeyForm::on_btnApply_clicked()
{
  tryUserAction();
  accept();
}

void AddForeignKeyForm::on_btnCancel_clicked()
{
  reject();
}

void AddForeignKeyForm::on_cmbReferenceTable_currentTextChanged(const QString &refTable)
{
  qDebug() << "Reference table selected:" << refTable;
  QStructureItemModel* structModel = DataStore::structureModel();
  QString refName = "qpsql://ughistory/tables/" + refTable;
  qDebug() << "Reference name:" << refName;
  DBTableItem* refObj =
      qobject_cast<DBTableItem*>(structModel->itemByName(refName));
  if (refObj) {
    qDebug() << "Reference table found:" << refName;
    refObj->reloadColumnsModel();
    ui->cmbReferenceColumn->setModel(refObj->columnsModel());
    ui->cmbReferenceColumn->setModelColumn(1);
  }
}
