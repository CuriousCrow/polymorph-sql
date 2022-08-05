#include "tableeditform.h"
#include "ui_tableeditform.h"
#include <QMessageBox>
#include <QDebug>
#include "../objects/appconst.h"
#include "../objects/dbuniqueconstraint.h"
#include "foreignkeyform.h"
#include "uniqueconstrainteditform.h"
#include "checkconstrainteditform.h"

#define CHK_PREFIX "chk_"
#define PK_PREFIX "pk_"
#define UQ_PREFIX "uq_"
#define FK_PREFIX "fk_"

TableEditForm::TableEditForm() :
  AbstractDatabaseEditForm(nullptr),
  ui(new Ui::TableEditForm)
{
  ui->setupUi(this);
  _colTypeDelegate = new ComboboxHashDelegate(ui->tableView);
  ui->tableView->setItemDelegateForColumn(COL_IDX_TYPE, _colTypeDelegate);

  _menuAddConstraint = new QMenu(this);
  _menuAddConstraint->addAction(tr("Primary Key"), this, &TableEditForm::onShowPrimaryKeyEditor);
  _menuAddConstraint->addAction(tr("Foreign Key"), this, &TableEditForm::onShowForeignKeyEditor);
  _menuAddConstraint->addAction(tr("Unique Constraint"), this, &TableEditForm::onShowUniqueConstraintEditor);
  _menuAddConstraint->addAction(tr("Check Constraint"), this, &TableEditForm::onShowCheckConstraintEditor);
  ui->btnAddConstraint->setMenu(_menuAddConstraint);
}

TableEditForm::~TableEditForm()
{
  delete ui;
}

void TableEditForm::objectToForm()
{
  QString tableName = _objItem->caption();
  setWindowTitle(tr("Table editor: ") + tableName);
  ui->lineEdit->setText(tableName);
  DBTableItem* tableItem = static_cast<DBTableItem*>(_objItem);
  tableItem->reloadColumnsModel();

  _colTypeDelegate->setItemsHash(_kb->typesHash(_objItem->driverName()));
  ui->tableView->setModel(tableItem->columnsModel());

  tableItem->reloadConstraintsModel();
  ui->tvConstraints->setModel(tableItem->constraintsModel());
}

void TableEditForm::formToObject()
{
  _objItem->setFieldValue(F_CAPTION, ui->lineEdit->text());
  //Модель автоматически обновится при редактировании
}

void TableEditForm::on_btnApply_clicked()
{
  tryUserAction();
}

void TableEditForm::on_btnClose_clicked()
{
  cancel();
}

void TableEditForm::on_btnAdd_clicked()
{
  static_cast<DBTableItem*>(_objItem)->addDefaultColumn();
}

void TableEditForm::on_btnDelete_clicked()
{
  int selectedRow = ui->tableView->currentIndex().row();
  if (selectedRow >= 0) {
    static_cast<DBTableItem*>(_objItem)->columnsModel()->removeRow(selectedRow);
  }
  else {
    QMessageBox::warning(this, tr(TITLE_WARNING), tr("Please, select the column you want to drop"));
  }
}

void TableEditForm::on_btnDropConstraint_clicked()
{
  QModelIndex curIdx = ui->tvConstraints->currentIndex();
  if (!curIdx.isValid())
    return;

  QString constraintName = ui->tvConstraints->model()->index(curIdx.row(), 1).data().toString();
  qDebug() << "Deleting constraint:" << constraintName;
  DBTableItem* tableItem = static_cast<DBTableItem*>(_objItem);
  DBConstraintItem* constraintItem = new DBConstraintItem(constraintName);
  constraintItem->setParentUrl(tableItem->objectUrl());
  constraintItem->setFieldValue(F_TABLE, tableItem->caption());

  ActionResult dropResult = constraintItem->deleteMe();
  constraintItem->deleteLater();
  if (dropResult.isSuccess()) {
    tableItem->reloadConstraintsModel();
  }
  else {
    QMessageBox::warning(this, tr(TITLE_WARNING), dropResult.description());
  }
}

void TableEditForm::onShowPrimaryKeyEditor()
{
  qDebug() << "Show primary key constraint editor";
  showCreateConstraintEditor(PK_PREFIX, DBObjectItem::PrimaryKey);
}

void TableEditForm::onShowForeignKeyEditor()
{
  qDebug() << "Show foreign key editor";
  showCreateConstraintEditor(FK_PREFIX, DBObjectItem::ForeignKey);
}

void TableEditForm::onShowUniqueConstraintEditor()
{
  qDebug() << "Show unique constraint editor";
  showCreateConstraintEditor(UQ_PREFIX, DBObjectItem::UniqueConstraint);
}

void TableEditForm::onShowCheckConstraintEditor()
{
  qDebug() << "Show check constraint editor";
  showCreateConstraintEditor(CHK_PREFIX, DBObjectItem::CheckConstraint);
}

void TableEditForm::showCreateConstraintEditor(QString namePrefix, DBObjectItem::ItemType objType)
{
  DBObjectItem* newItemObj = _core->newObjInstance(_objItem->driverName(), objType);
  newItemObj->setFieldValue(F_CAPTION, namePrefix + _objItem->caption());
  newItemObj->setFieldValue(F_TABLE, _objItem->caption());
  newItemObj->setParentUrl(_objItem->objectUrl());
  openConstraintEditor(newItemObj, AbstractDatabaseEditForm::Create);
}

void TableEditForm::showViewConstraintEditor(const QModelIndex& index)
{
  DBTableItem* tableItem = static_cast<DBTableItem*>(_objItem);

  QAbstractTableModel* model = tableItem->constraintsModel();
  QString constType = model->index(index.row(), 0).data().toString();
  QString constName = model->index(index.row(), 1).data().toString();

  DBObjectItem::ItemType type;
  if (constType == "FOREIGN KEY") {
    type = DBObjectItem::ItemType::ForeignKey;
  }
  else if (constType == "PRIMARY KEY") {
    type = DBObjectItem::ItemType::PrimaryKey;
  }
  else if (constType == "UNIQUE") {
    type = DBObjectItem::ItemType::UniqueConstraint;
  }
  else if (constType == "CHECK") {
    type = DBObjectItem::ItemType::CheckConstraint;
  }
  else {
    return;
  }
  DBObjectItem* constItem = _core->newObjInstance(tableItem->driverName(), type);
  constItem->setFieldValue(F_CAPTION, constName);
  constItem->setFieldValue(F_TABLE, tableItem->caption());
  constItem->setParentUrl(tableItem->objectUrl());
  openConstraintEditor(constItem, AbstractDatabaseEditForm::Edit);
}

void TableEditForm::openConstraintEditor(DBObjectItem *obj, AbstractDatabaseEditForm::UserAction action)
{
  qDebug() << "Open constraint editor";
  DBTableItem* tableItem = static_cast<DBTableItem*>(_objItem);
  AbstractDatabaseEditForm* constraintForm = _core->objectForm(tableItem->driverName(), (DBObjectItem::ItemType)obj->type());
  constraintForm->setUserAction(action);
  constraintForm->setObjItem(obj);
  constraintForm->objectToForm();
  constraintForm->setWindowTitle(action == AbstractDatabaseEditForm::Create ?
                                   tr("New constraint") : tr("Edit constraint"));
  connect(constraintForm, &ForeignKeyForm::accepted,
          this, &TableEditForm::onNewConstraintApply);
  connect(constraintForm, &ForeignKeyForm::rejected,
          this, &TableEditForm::onNewConstraintCancel);
  constraintForm->show();
}

void TableEditForm::onNewConstraintApply()
{
  DBTableItem* tableItem = static_cast<DBTableItem*>(_objItem);
  sender()->deleteLater();
  tableItem->reloadConstraintsModel();
}

void TableEditForm::onNewConstraintCancel()
{
  sender()->deleteLater();
}

void TableEditForm::on_tvConstraints_doubleClicked(const QModelIndex &index)
{
  showViewConstraintEditor(index);
}
