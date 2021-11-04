#include "vieweditdialog.h"
#include "ui_vieweditdialog.h"
#include "../objects/appconst.h"
#include <QMessageBox>
#include <QDebug>
#include <QTableView>
#include <QHeaderView>

ViewEditDialog::ViewEditDialog() :
  AbstractDatabaseEditForm(nullptr),
  ui(new Ui::ViewEditDialog)
{
  ui->setupUi(this);
  connect(this, SIGNAL(userActionChanged()), SLOT(onUserActionChanged()));
}

ViewEditDialog::~ViewEditDialog()
{
  delete ui;
}

void ViewEditDialog::inject_kb_into_kb(LKnowledgeBase *kb)
{
  _kb = kb;
  _knowledgeModel = new JointDBOjbectModel(this);
  _knowledgeModel->registerColumn(F_NAME);
  _knowledgeModel->registerColumn(F_TYPE);
  _knowledgeModel->registerColumn(F_DESCRIPTION);
  _knowledgeModel->registerColumn(F_DOC_LINK);

  _objectsModel = new LDBObjectTableModel(this);
  _objectsModel->registerColumn(F_NAME);
  _objectsModel->registerColumn(F_TYPE);
  _objectsModel->registerColumn(F_DESCRIPTION);
  _objectsModel->registerColumn(F_DOC_LINK);
  _objectsModel->setFixedValue(F_DESCRIPTION, "");
  _objectsModel->setFixedValue(F_DOC_LINK, "");

  _completer = new LTextCompleter(_knowledgeModel, this);
  QTableView* completerView = new QTableView(this);
  completerView->horizontalHeader()->hide();
  completerView->verticalHeader()->hide();
  completerView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  _completer->setPopup(completerView);
  _completer->setCaseSensitivity(Qt::CaseInsensitive);
  _completer->setWidget(ui->edtQueryText);
}

void ViewEditDialog::on_btnOk_clicked()
{
  tryUserAction();
}

void ViewEditDialog::on_btnCancel_clicked()
{
  if (userAction() == AbstractDatabaseEditForm::Create) {
    delete  _objItem;
  }
  reject();
}

void ViewEditDialog::onUserActionChanged()
{
  ui->edtName->setReadOnly(userAction() != UserAction::Create);
  ui->edtQueryText->setReadOnly(userAction() != UserAction::Create);
  ui->btnOk->setEnabled(userAction() == UserAction::Create);
  ui->btnCancel->setText(userAction() == UserAction::Create ? tr("Cancel") : tr("Close"));
}

void ViewEditDialog::objectToForm()
{
  _knowledgeModel->clear();

  DBDatabaseItem* dbObj = _ds->databaseItem(_objItem);
  _knowledgeModel->addModel(FOLDER_KEYWORDS, _kb->modelByType(OBJTYPE_KEYWORD, dbObj->driverName()));
  _knowledgeModel->addModel(FOLDER_FUNCTIONS, _kb->modelByType(OBJTYPE_FUNCTION, dbObj->driverName()));
  _objectsModel->setQuery(dbObj->getAllObjectListSql());
  _objectsModel->reload(dbObj->connectionName());
  _knowledgeModel->addModel(FOLDER_OBJECTS, _objectsModel);

  ui->edtName->setText(_objItem->caption());
  ui->edtQueryText->setPlainText(_objItem->fieldValue(F_QUERY_TEXT).toString());
}

void ViewEditDialog::formToObject()
{
  _objItem->setFieldValue(F_CAPTION, ui->edtName->text());
  _objItem->setFieldValue(F_QUERY_TEXT, ui->edtQueryText->toPlainText());
}

void ViewEditDialog::localEvent(LocalEvent *event)
{
  qDebug() << "View edit dialog event:" << event->type();
}
