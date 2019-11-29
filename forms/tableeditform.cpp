#include "tableeditform.h"
#include "ui_tableeditform.h"
#include <QMessageBox>
#include <QDebug>
#include "../dbms/appconst.h"
#include "../qknowledgebase.h"


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
  QDBTableItem* tableItem = qobject_cast<QDBTableItem*>(_objItem);
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
  qobject_cast<QDBTableItem*>(_objItem)->addDefaultColumn();
}

void TableEditForm::on_btnDelete_clicked()
{
  int selectedRow = ui->tableView->currentIndex().row();
  if (selectedRow >= 0) {
    qobject_cast<QDBTableItem*>(_objItem)->columnsModel()->removeRow(selectedRow);
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
  QDBTableItem* tableItem = qobject_cast<QDBTableItem*>(_objItem);
  QDBConstraintItem* constraintItem = new QDBConstraintItem(constraintName);
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
  QDBTableItem* tableItem = qobject_cast<QDBTableItem*>(_objItem);
  AddForeignKeyForm* foreignKeyForm = new AddForeignKeyForm(this);
  foreignKeyForm->setUserAction(AbstractDatabaseEditForm::Create);
  QDBForeignKey* newFkObj = tableItem->newForeignKey();
  newFkObj->setFieldValue(F_TABLE, tableItem->fieldValue(F_CAPTION));
  newFkObj->setParentUrl(tableItem->objectUrl());
  foreignKeyForm->setObjItem(newFkObj);
  foreignKeyForm->objectToForm();
  connect(foreignKeyForm, &AddForeignKeyForm::accepted,
          this, &TableEditForm::onNewForeignKeySuccess);
  connect(foreignKeyForm, &AddForeignKeyForm::rejected,
          this, &TableEditForm::onNewForeignKeyCanceled);
  foreignKeyForm->show();
}

void TableEditForm::onShowUniqueConstraintEditor()
{
  qDebug() << "Show unique constraint editor";
}

void TableEditForm::onShowCheckConstraintEditor()
{
  qDebug() << "Show check constraint editor";
}

void TableEditForm::onNewForeignKeySuccess()
{
  QDBTableItem* tableItem = qobject_cast<QDBTableItem*>(_objItem);
  sender()->deleteLater();
  tableItem->reloadConstraintsModel();
}

void TableEditForm::onNewForeignKeyCanceled()
{
  sender()->deleteLater();
}
