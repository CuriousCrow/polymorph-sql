#include "mysqlprocedureeditform.h"
#include "ui_mysqlprocedureeditform.h"

#include "models/comboboxitemdelegate.h"
#include "objects/mysqlprocedure.h"
#include "objects/appconst.h"

MysqlProcedureEditForm::MysqlProcedureEditForm() :
  AbstractDatabaseEditForm(nullptr),
  ui(new Ui::MysqlProcedureEditForm)
{
  ui->setupUi(this);

  _typesDelegate = new ComboboxItemDelegate(this);

  ComboboxItemDelegate* modeDelegate = new ComboboxItemDelegate();
  QStringList modes;
  modes << "IN" << "OUT";
  modeDelegate->setOptions(modes);
  ui->tvArguments->setItemDelegateForColumn(0, modeDelegate);
}

MysqlProcedureEditForm::~MysqlProcedureEditForm()
{
  delete ui;
}

void MysqlProcedureEditForm::on_btnApply_clicked()
{
  tryUserAction();
}

void MysqlProcedureEditForm::on_btnClose_clicked()
{
  cancel();
}

void MysqlProcedureEditForm::objectToForm()
{
  _editorSupport->setEditor(ui->teSource);
  _editorSupport->updateModels(_objItem);

  _typeProvider->setItemObject(_objItem);
  _typesDelegate->setOptions(_typeProvider->typeNames());
  ui->tvArguments->setItemDelegateForColumn(2, _typesDelegate);

  MysqlProcedure* procObj = static_cast<MysqlProcedure*>(_objItem);
  _argModel = procObj->argumentModel();
  ui->tvArguments->setModel(_argModel);
  ui->edtName->setText(procObj->caption());
  ui->teSource->setPlainText(procObj->fieldValue(F_SOURCE_CODE).toString());
}

void MysqlProcedureEditForm::formToObject()
{
  _objItem->setFieldValue(F_CAPTION, ui->edtName->text());
  _objItem->setFieldValue(F_SOURCE_CODE, ui->teSource->toPlainText());
}

void MysqlProcedureEditForm::on_edtName_textChanged(const QString &name)
{
  this->setWindowTitle(tr("Procedure: ") + name);
}

void MysqlProcedureEditForm::on_btnAddArg_clicked()
{
  QVariantMap row;
  row.insert(F_ID, ++_maxId);
  _argModel->addRow(row);
}

void MysqlProcedureEditForm::on_btnDeleteArg_clicked()
{
  _argModel->deleteByRow(ui->tvArguments->currentIndex().row());
}
