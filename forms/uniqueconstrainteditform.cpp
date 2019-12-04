#include "uniqueconstrainteditform.h"
#include "ui_uniqueconstrainteditform.h"
#include "core/datastore.h"
#include "dbms/appconst.h"

UniqueConstraintEditForm::UniqueConstraintEditForm(QWidget *parent) :
  AbstractDatabaseEditForm(parent),
  ui(new Ui::UniqueConstraintEditForm)
{
  ui->setupUi(this);
}

UniqueConstraintEditForm::~UniqueConstraintEditForm()
{
  delete ui;
}


void UniqueConstraintEditForm::objectToForm()
{
  ui->edtName->setText(_objItem->fieldValue(F_CAPTION).toString());

  DBTableItem* targetObj =
      qobject_cast<DBTableItem*>(DataStore::itemByFolderAndName(_objItem, FOLDER_TABLES, _objItem->fieldValue(F_TABLE).toString()));
  ui->lvColumns->setModel(targetObj->columnsModel());
  ui->lvColumns->setModelColumn(1);
}

void UniqueConstraintEditForm::formToObject()
{
  _objItem->setFieldValue(F_CAPTION, ui->edtName->text());
  QStringList colums;
  foreach(QModelIndex idx, ui->lvColumns->selectionModel()->selectedIndexes()) {
    colums.append(idx.data().toString());
  }
  _objItem->setFieldValue(F_COLUMN, colums.join(","));
}

void UniqueConstraintEditForm::on_btnApply_clicked()
{
  tryUserAction();
}

void UniqueConstraintEditForm::on_btnCancel_clicked()
{
  reject();
}
