#include "addforeignkeyform.h"
#include "ui_addforeignkeyform.h"
#include <QDebug>
#include "dbms/appconst.h"
#include "core/datastore.h"
#include "dbms/appurl.h"

AddForeignKeyForm::AddForeignKeyForm(QWidget *parent) :
  AbstractDatabaseEditForm(parent),
  ui(new Ui::AddForeignKeyForm)
{
  ui->setupUi(this);
  connect(this, &AddForeignKeyForm::userActionChanged,
          this, &AddForeignKeyForm::onUserActionChanged);
}

AddForeignKeyForm::~AddForeignKeyForm()
{
  qDebug() << "Add foreign key destructor";
  delete ui;
}

void AddForeignKeyForm::objectToForm()
{
  ui->cmbReferenceTable->setModel(DataStore::structureModel());
  ui->cmbReferenceTable->setRootModelIndex(DataStore::itemIdx(_objItem, FOLDER_TABLES));

  DBTableItem* targetObj =
      qobject_cast<DBTableItem*>(DataStore::itemByFolderAndName(_objItem, FOLDER_TABLES, _objItem->fieldValue(F_TABLE).toString()));
  ui->cmbTargetColumn->setModel(targetObj->columnsModel());
  ui->cmbTargetColumn->setModelColumn(1);

  ui->edtName->setText(_objItem->fieldValue(F_CAPTION).toString());
  ui->cmbTargetColumn->setCurrentText(_objItem->fieldValue(F_COLUMN).toString());
  ui->cmbReferenceTable->setCurrentText(_objItem->fieldValue(F_REFTABLE).toString());
  ui->cmbReferenceColumn->setCurrentText(_objItem->fieldValue(F_REFCOLUMN).toString());
  ui->cmbOnUpdateAction->setCurrentText(_objItem->fieldValue(F_ON_UPDATE).toString());
  ui->cmbOnDeleteAction->setCurrentText(_objItem->fieldValue(F_ON_DELETE).toString());

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
}

void AddForeignKeyForm::on_btnCancel_clicked()
{
  reject();
}

void AddForeignKeyForm::on_cmbReferenceTable_currentTextChanged(const QString &refTable)
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

void AddForeignKeyForm::onUserActionChanged()
{
  ui->edtName->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->cmbTargetColumn->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->cmbReferenceTable->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->cmbReferenceColumn->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->cmbOnUpdateAction->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->cmbOnDeleteAction->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->btnApply->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
}
