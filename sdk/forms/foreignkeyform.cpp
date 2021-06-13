#include "foreignkeyform.h"
#include "ui_foreignkeyform.h"
#include <QDebug>
#include "../objects/appconst.h"
#include "sdk/core/datastore.h"
#include "../objects/appurl.h"

ForeignKeyForm::ForeignKeyForm(QWidget *parent) :
  AbstractDatabaseEditForm(parent),
  ui(new Ui::ForeignKeyForm)
{
  ui->setupUi(this);
  connect(this, &ForeignKeyForm::userActionChanged,
          this, &ForeignKeyForm::onUserActionChanged);
}

ForeignKeyForm::~ForeignKeyForm()
{
  qDebug() << "Add foreign key destructor";
  delete ui;
}

void ForeignKeyForm::objectToForm()
{
  ui->cmbReferenceTable->setModel(DataStore::structureModel());
  ui->cmbReferenceTable->setRootModelIndex(DataStore::itemIdx(_objItem, FOLDER_TABLES));

  DBTableItem* targetObj =
      qobject_cast<DBTableItem*>(DataStore::itemByFolderAndName(_objItem, FOLDER_TABLES, _objItem->fieldValue(F_TABLE).toString()));
  ui->cmbTargetColumn->setModel(targetObj->columnsModel());
  ui->cmbTargetColumn->setModelColumn(1);

  ui->edtName->setText(_objItem->caption());
  ui->cmbTargetColumn->setCurrentText(_objItem->fieldValue(F_COLUMN).toString());
  ui->cmbReferenceTable->setCurrentText(_objItem->fieldValue(F_REFTABLE).toString());
  ui->cmbReferenceColumn->setCurrentText(_objItem->fieldValue(F_REFCOLUMN).toString());
  ui->cmbOnUpdateAction->setCurrentText(_objItem->fieldValue(F_ON_UPDATE).toString());
  ui->cmbOnDeleteAction->setCurrentText(_objItem->fieldValue(F_ON_DELETE).toString());

  _objItem->submit();
}

void ForeignKeyForm::formToObject()
{
  _objItem->setFieldValue(F_CAPTION, ui->edtName->text());
  _objItem->setFieldValue(F_COLUMN, ui->cmbTargetColumn->currentText());
  _objItem->setFieldValue(F_REFTABLE, ui->cmbReferenceTable->currentText());
  _objItem->setFieldValue(F_REFCOLUMN, ui->cmbReferenceColumn->currentText());
  _objItem->setFieldValue(F_ON_UPDATE, ui->cmbOnUpdateAction->currentText());
  _objItem->setFieldValue(F_ON_DELETE, ui->cmbOnDeleteAction->currentText());
}

void ForeignKeyForm::on_btnApply_clicked()
{
  tryUserAction();
}

void ForeignKeyForm::on_btnCancel_clicked()
{
  reject();
}

void ForeignKeyForm::on_cmbReferenceTable_currentTextChanged(const QString &refTable)
{
  DBTableItem* refObj =
      qobject_cast<DBTableItem*>(DataStore::itemByFolderAndName(_objItem, FOLDER_TABLES, refTable));
  if (refObj) {
    qDebug() << "Reference table found";
    refObj->reloadColumnsModel();
    ui->cmbReferenceColumn->setModel(refObj->columnsModel());
    ui->cmbReferenceColumn->setModelColumn(1);
  }
}

void ForeignKeyForm::onUserActionChanged()
{
  ui->edtName->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->cmbTargetColumn->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->cmbReferenceTable->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->cmbReferenceColumn->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->cmbOnUpdateAction->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->cmbOnDeleteAction->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->btnApply->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
}
