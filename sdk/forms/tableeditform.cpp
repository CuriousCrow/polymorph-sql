#include "tableeditform.h"
#include "ui_tableeditform.h"
#include <QMessageBox>
#include <QDebug>
#include "../objects/appconst.h"
#include "../objects/dbuniqueconstraint.h"
#include "../../qknowledgebase.h"
#include "foreignkeyform.h"
#include "uniqueconstrainteditform.h"
#include "checkconstrainteditform.h"


TableEditForm::TableEditForm(QWidget *parent) :
  AbstractDatabaseEditForm(parent),
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
  setWindowTitle("Table editor: " + tableName);
  ui->lineEdit->setText(tableName);
  DBTableItem* tableItem = qobject_cast<DBTableItem*>(_objItem);
  tableItem->reloadColumnsModel();

  _colTypeDelegate->setItemsHash(QKnowledgeBase::kb()->typesHash(_objItem->driverName()));
  ui->tableView->setModel(tableItem->columnsModel());

  tableItem->reloadConstraintsModel();
  ui->tvConstraints->setModel(tableItem->constraintsModel());
}

void TableEditForm::formToObject()
{
  _objItem->setFieldValue(F_CAPTION, ui->lineEdit->text());
  //Модель автоматически обновится при редактировании
}

void TableEditForm::on_pushButton_clicked()
{
  tryUserAction();
}

void TableEditForm::on_pushButton_2_clicked()
{
  reject();
}

void TableEditForm::on_btnAdd_clicked()
{
  qobject_cast<DBTableItem*>(_objItem)->addDefaultColumn();
}

void TableEditForm::on_btnDelete_clicked()
{
  int selectedRow = ui->tableView->currentIndex().row();
  if (selectedRow >= 0) {
    qobject_cast<DBTableItem*>(_objItem)->columnsModel()->removeRow(selectedRow);
  }
  else {
    QMessageBox::warning(this, tr(TITLE_WARNING), "Please, select the column you want to drop");
  }
}

void TableEditForm::on_btnDropConstraint_clicked()
{
  QModelIndex curIdx = ui->tvConstraints->currentIndex();
  if (!curIdx.isValid())
    return;

  QString constraintName = ui->tvConstraints->model()->index(curIdx.row(), 1).data().toString();
  qDebug() << "Deleting constraint:" << constraintName;
  DBTableItem* tableItem = qobject_cast<DBTableItem*>(_objItem);
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
  qDebug() << "Show unique constraint editor";
  DBTableItem* tableItem = qobject_cast<DBTableItem*>(_objItem);
  UniqueConstraintEditForm* primaryKeyForm = new UniqueConstraintEditForm(this);
  primaryKeyForm->setUserAction(AbstractDatabaseEditForm::Create);
  DBConstraintItem* newPkObj = tableItem->newPrimaryKey();
  newPkObj->setFieldValue(F_TABLE, tableItem->caption());
  newPkObj->setParentUrl(tableItem->objectUrl());
  primaryKeyForm->setObjItem(newPkObj);
  primaryKeyForm->objectToForm();
  primaryKeyForm->setWindowTitle("New primary key");
  connect(primaryKeyForm, &ForeignKeyForm::accepted,
          this, &TableEditForm::onNewConstraintApply);
  connect(primaryKeyForm, &ForeignKeyForm::rejected,
          this, &TableEditForm::onNewConstraintCancel);
  primaryKeyForm->show();
}

void TableEditForm::onShowForeignKeyEditor()
{
  qDebug() << "Show foreign key editor";
  DBTableItem* tableItem = qobject_cast<DBTableItem*>(_objItem);
  ForeignKeyForm* foreignKeyForm = new ForeignKeyForm(this);
  foreignKeyForm->setUserAction(AbstractDatabaseEditForm::Create);
  DBForeignKey* newFkObj = tableItem->newForeignKey();
  newFkObj->setFieldValue(F_TABLE, tableItem->caption());
  newFkObj->setParentUrl(tableItem->objectUrl());
  foreignKeyForm->setObjItem(newFkObj);
  foreignKeyForm->objectToForm();
  connect(foreignKeyForm, &ForeignKeyForm::accepted,
          this, &TableEditForm::onNewConstraintApply);
  connect(foreignKeyForm, &ForeignKeyForm::rejected,
          this, &TableEditForm::onNewConstraintCancel);
  foreignKeyForm->show();
}

void TableEditForm::onShowUniqueConstraintEditor()
{
  qDebug() << "Show unique constraint editor";
  DBTableItem* tableItem = qobject_cast<DBTableItem*>(_objItem);
  UniqueConstraintEditForm* uniqueKeyForm = new UniqueConstraintEditForm(this);
  uniqueKeyForm->setUserAction(AbstractDatabaseEditForm::Create);
  DBUniqueConstraint* newFkObj = tableItem->newUniqueConstraint();
  newFkObj->setFieldValue(F_TABLE, tableItem->caption());
  newFkObj->setParentUrl(tableItem->objectUrl());
  uniqueKeyForm->setObjItem(newFkObj);
  uniqueKeyForm->objectToForm();
  uniqueKeyForm->setWindowTitle("New unique constraint");
  connect(uniqueKeyForm, &ForeignKeyForm::accepted,
          this, &TableEditForm::onNewConstraintApply);
  connect(uniqueKeyForm, &ForeignKeyForm::rejected,
          this, &TableEditForm::onNewConstraintCancel);
  uniqueKeyForm->show();
}

void TableEditForm::onShowCheckConstraintEditor()
{
  qDebug() << "Show check constraint editor";
  DBTableItem* tableItem = qobject_cast<DBTableItem*>(_objItem);
  CheckConstraintEditForm* checkConstraintForm = new CheckConstraintEditForm(this);
  checkConstraintForm->setUserAction(AbstractDatabaseEditForm::Create);
  DBCheckConstraint* newCheckObj = tableItem->newCheckConstraint();
  newCheckObj->setFieldValue(F_TABLE, tableItem->caption());
  newCheckObj->setParentUrl(tableItem->objectUrl());
  checkConstraintForm->setObjItem(newCheckObj);
  checkConstraintForm->objectToForm();
  checkConstraintForm->setWindowTitle("New check constraint");
  connect(checkConstraintForm, &ForeignKeyForm::accepted,
          this, &TableEditForm::onNewConstraintApply);
  connect(checkConstraintForm, &ForeignKeyForm::rejected,
          this, &TableEditForm::onNewConstraintCancel);
  checkConstraintForm->show();
}

void TableEditForm::onNewConstraintApply()
{
  DBTableItem* tableItem = qobject_cast<DBTableItem*>(_objItem);
  sender()->deleteLater();
  tableItem->reloadConstraintsModel();
}

void TableEditForm::onNewConstraintCancel()
{
  sender()->deleteLater();
}

void TableEditForm::on_tvConstraints_doubleClicked(const QModelIndex &index)
{
  DBTableItem* tableItem = qobject_cast<DBTableItem*>(_objItem);

  QAbstractTableModel* model = tableItem->constraintsModel();
  QString constType = model->index(index.row(), 0).data().toString();
  QString constName = model->index(index.row(), 1).data().toString();
  AbstractDatabaseEditForm* form;
  DBObjectItem* obj;
  if (constType == "FOREIGN KEY") {
    form = new ForeignKeyForm(this);
    form->setWindowTitle("Foreign key editor: " + constName);
    obj = tableItem->newForeignKey();
  }
  else if (constType == "PRIMARY KEY") {
    form = new UniqueConstraintEditForm(this);
    form->setWindowTitle("Primary key editor: " + constName);
    obj = tableItem->newPrimaryKey();
  }
  else if (constType == "UNIQUE") {
    form = new UniqueConstraintEditForm(this);
    form->setWindowTitle("Unique constraint editor: " + constName);
    obj = tableItem->newUniqueConstraint();
  }
  else if (constType == "CHECK") {
    form = new CheckConstraintEditForm(this);
    form->setWindowTitle("Check constraint editor: " + constName);
    obj = tableItem->newCheckConstraint();
  }
  else {
    return;
  }
  form->setUserAction(AbstractDatabaseEditForm::Edit);
  obj->setFieldValue(F_TABLE, tableItem->caption());
  obj->setFieldValue(F_CAPTION, constName);
  obj->setParentUrl(tableItem->objectUrl());
  obj->refresh();

  form->setObjItem(obj);
  form->objectToForm();
  connect(form, &ForeignKeyForm::accepted,
          this, &TableEditForm::onNewConstraintApply);
  connect(form, &ForeignKeyForm::rejected,
          this, &TableEditForm::onNewConstraintCancel);
  form->show();
}
