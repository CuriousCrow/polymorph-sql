#include "procedureeditform.h"
#include "ui_procedureeditform.h"
#include <QTableView>
#include <QHeaderView>
#include "objects/appconst.h"
#include "widgets/lqueryeditor.h"

ProcedureEditForm::ProcedureEditForm() :
  AbstractDatabaseEditForm(nullptr),
  ui(new Ui::ProcedureEditForm)
{
  ui->setupUi(this);
  connect(this, SIGNAL(userActionChanged()), SLOT(onUserActionChanged()));

//  _helpTooltip = new LSimpleTooltip(this);
//  _helpTooltip->setOpenExternalLinks(true);
//  _helpTooltip->setWidget(ui->edtSourceCode);

//  LKeySequenceInterceptor* keyInterceptor = new LKeySequenceInterceptor(this);
//  keyInterceptor->setKeySequence(QKeySequence(Qt::CTRL, Qt::Key_Q));
//  keyInterceptor->applyToWidget(ui->edtSourceCode);
//  connect(keyInterceptor, SIGNAL(keySequencePressed(QKeySequence)),
//          this, SLOT(onHelpKey()));
}

ProcedureEditForm::~ProcedureEditForm()
{
  delete ui;
}

//void ProcedureEditForm::inject_sqlCompleterSupport_into_form(SimpleSqlCompleterSupport *completerSupport)
//{
//  _completerSupport = completerSupport;
//  _completerSupport->setParent(this);
//  _completerSupport->setWidget(ui->edtSourceCode);
//}

//void ProcedureEditForm::inject_helpLookupProvider(SqlHelpLookupProvider *lookupProvider)
//{
//  _helpLookupProvider = lookupProvider;
//  _helpTooltip->setLookupProvider(_helpLookupProvider);
//}

//void ProcedureEditForm::inject_by_sqlSyntaxHighlighter(LSqlSyntaxHighlighter *syntaxHighlighter)
//{
//  _highlighter = syntaxHighlighter;
//  _highlighter->setParent(this);
//  _highlighter->setDocument(ui->edtSourceCode->document());
//}

void ProcedureEditForm::reloadTypes()
{
  QHash<int, QString> types = _kb->typesHash(_objItem->driverName());
  ui->cmbResultType->clear();
  ui->cmbResultType->addItem("void");
  ui->cmbResultType->addItem("trigger");
  QStringList values = types.values();
  foreach (QString type, values) {
    ui->cmbResultType->addItem(type.toLower());
  }
}

void ProcedureEditForm::objectToForm()
{
  _editorSupport->setEditor(ui->edtSourceCode);
  _editorSupport->updateModels(_objItem);
//  _completerSupport->setItem(_objItem);
//  _highlighter->updateModels(_objItem->driverName());
//  _helpLookupProvider->updateHelpModels(_objItem->driverName());

  reloadTypes();
  ui->edtName->setText(_objItem->caption());
  ui->edtSourceCode->setPlainText(_objItem->fieldValue(F_SOURCE_CODE).toString());
  ui->cmbLanguage->setCurrentText(_objItem->fieldValue(F_LANGUAGE).toString());
  ui->cmbResultType->setCurrentText(_objItem->fieldValue(F_RETURN_TYPE).toString());
}

void ProcedureEditForm::formToObject()
{
  _objItem->setFieldValue(F_CAPTION, ui->edtName->text());
  _objItem->setFieldValue(F_SOURCE_CODE, ui->edtSourceCode->toPlainText());
  _objItem->setFieldValue(F_LANGUAGE, ui->cmbLanguage->currentText());
  _objItem->setFieldValue(F_RETURN_TYPE, ui->cmbResultType->currentText());
}

void ProcedureEditForm::on_btnApply_clicked()
{
  tryUserAction();
}

void ProcedureEditForm::on_btnCancel_clicked()
{
  reject();
}

void ProcedureEditForm::onUserActionChanged()
{
  ui->edtName->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->cmbLanguage->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
  ui->cmbResultType->setEnabled(userAction() == AbstractDatabaseEditForm::Create);
}

//void ProcedureEditForm::onHelpKey()
//{
//  _helpTooltip->popup(ui->edtSourceCode->currentWord(),
//                      ui->edtSourceCode->cursorGlobalPos());
//}
