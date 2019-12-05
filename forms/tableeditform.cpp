#include "tableeditform.h"
#include "ui_tableeditform.h"
#include <QMessageBox>
#include <QDebug>
#include "../dbms/appconst.h"
#include "../dbms/dbuniqueconstraint.h"
#include "../qknowledgebase.h"
#include "addforeignkeyform.h"
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
  _menuAddConstraint->addAction(trUtf8("Add Foreign Key"), this, &TableEditForm::onShowForeignKeyEditor);
  _menuAddConstraint->addAction(trUtf8("Add Unique Constraint"), this, &TableEditForm::onShowUniqueConstraintEditor);
  _menuAddConstraint->addAction(trUtf8("Add Check Constraint"), this, &TableEditForm::onShowCheckConstraintEditor);
  ui->btnAddConstraint->setMenu(_menuAddConstraint);
}

TableEditForm::~TableEditForm()
{
  delete ui;
}

void TableEditForm::objectToForm()
{
  QString tableName = _objItem->fieldValue(F_CAPTION).toString();
  setWindowTitle("Редактор таблицы " + tableName);
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
    QMessageBox::warning(this, trUtf8(TITLE_WARNING), "Please, select the column you want to drop");
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
  constraintItem->setFieldValue(F_TABLE, tableItem->fieldValue(F_CAPTION));

  ActionResult dropResult = constraintItem->deleteMe();
  constraintItem->deleteLater();
  if (dropResult.isSuccess()) {
    tableItem->reloadConstraintsModel();
  }
  else {
    QMessageBox::warning(this, trUtf8(TITLE_WARNING), dropResult.description());
  }
}

void TableEditForm::onShowForeignKeyEditor()
{
  qDebug() << "Show foreign key editor";
  DBTableItem* tableItem = qobject_cast<DBTableItem*>(_objItem);
  AddForeignKeyForm* foreignKeyForm = new AddForeignKeyForm(this);
  foreignKeyForm->setUserAction(AbstractDatabaseEditForm::Create);
  DBForeignKey* newFkObj = tableItem->newForeignKey();
  newFkObj->setFieldValue(F_TABLE, tableItem->fieldValue(F_CAPTION));
  newFkObj->setParentUrl(tableItem->objectUrl());
  foreignKeyForm->setObjItem(newFkObj);
  foreignKeyForm->objectToForm();
  connect(foreignKeyForm, &AddForeignKeyForm::accepted,
          this, &TableEditForm::onNewConstraintApply);
  connect(foreignKeyForm, &AddForeignKeyForm::rejected,
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
  newFkObj->setFieldValue(F_TABLE, tableItem->fieldValue(F_CAPTION));
  newFkObj->setParentUrl(tableItem->objectUrl());
  uniqueKeyForm->setObjItem(newFkObj);
  uniqueKeyForm->objectToForm();
  connect(uniqueKeyForm, &AddForeignKeyForm::accepted,
          this, &TableEditForm::onNewConstraintApply);
  connect(uniqueKeyForm, &AddForeignKeyForm::rejected,
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
  newCheckObj->setFieldValue(F_TABLE, tableItem->fieldValue(F_CAPTION));
  newCheckObj->setParentUrl(tableItem->objectUrl());
  checkConstraintForm->setObjItem(newCheckObj);
  checkConstraintForm->objectToForm();
  connect(checkConstraintForm, &AddForeignKeyForm::accepted,
          this, &TableEditForm::onNewConstraintApply);
  connect(checkConstraintForm, &AddForeignKeyForm::rejected,
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
  AbstractDatabaseEditForm* form;
  DBObjectItem* obj;
  if (constType == "FOREIGN KEY") {
    form = new AddForeignKeyForm(this);
    obj = tableItem->newForeignKey();
  }
  else if (constType == "UNIQUE") {
    form = new UniqueConstraintEditForm(this);
    obj = tableItem->newUniqueConstraint();
  }
  else if (constType == "CHECK") {
    form = new CheckConstraintEditForm(this);
    obj = tableItem->newCheckConstraint();
  }
  else {
    return;
  }
  QString constName = model->index(index.row(), 1).data().toString();
  form->setUserAction(AbstractDatabaseEditForm::Edit);
  obj->setFieldValue(F_TABLE, tableItem->fieldValue(F_CAPTION));
  obj->setFieldValue(F_CAPTION, constName);
  obj->setParentUrl(tableItem->objectUrl());
  obj->refresh();

  form->setObjItem(obj);
  form->objectToForm();
  connect(form, &AddForeignKeyForm::accepted,
          this, &TableEditForm::onNewConstraintApply);
  connect(form, &AddForeignKeyForm::rejected,
          this, &TableEditForm::onNewConstraintCancel);
  form->show();
}
