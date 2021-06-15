#include "uniqueconstrainteditform.h"
#include "ui_uniqueconstrainteditform.h"
#include "../core/datastore.h"
#include "../objects/appconst.h"

UniqueConstraintEditForm::UniqueConstraintEditForm(QWidget *parent) :
  AbstractDatabaseEditForm(parent),
  ui(new Ui::UniqueConstraintEditForm)
{
  ui->setupUi(this);
  connect(this, &UniqueConstraintEditForm::userActionChanged,
          this, &UniqueConstraintEditForm::onUserActionChanged);
}

UniqueConstraintEditForm::~UniqueConstraintEditForm()
{
  delete ui;
}


void UniqueConstraintEditForm::objectToForm()
{
  ui->edtName->setText(_objItem->caption());

  DBTableItem* targetObj =
      static_cast<DBTableItem*>(DataStore::itemByFolderAndName(_objItem, FOLDER_TABLES, _objItem->fieldValue(F_TABLE).toString()));
  SqlColumnModel* colModel = targetObj->columnsModel();
  ui->lvColumns->setModel(colModel);
  ui->lvColumns->setModelColumn(1);


  QStringList columns = _objItem->fieldValue(F_COLUMN).toString().split(",");
  foreach(QString colName, columns) {
    int row = colModel->rowByName(colName);
    ui->lvColumns->selectionModel()->select(colModel->index(row, 1), QItemSelectionModel::Select);
  }
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

void UniqueConstraintEditForm::onUserActionChanged()
{
  ui->edtName->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->lvColumns->setSelectionMode(userAction() == AbstractDatabaseEditForm::Create ?
                                    QAbstractItemView::MultiSelection : QAbstractItemView::NoSelection);
  ui->btnApply->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
}
