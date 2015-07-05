#include "queryeditorwindow.h"
#include "ui_queryeditorwindow.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

QueryEditorWindow::QueryEditorWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::QueryEditorWindow)
{
  ui->setupUi(this);

  _resultModel = new QSqlQueryModel(this);
  ui->tvResultSet->setModel(_resultModel);

  _activeConnectionModel = new QActiveConnectionModel(this);
  ui->cmbDatabase->setModel(_activeConnectionModel);
  ui->cmbDatabase->setModelColumn(0);

  QSqlSyntaxHighlighter* highlighter = new QSqlSyntaxHighlighter(this);
  highlighter->setDocument(ui->teQueryEditor->document());

  //Simple keywords autocompleter
  //TODO: Dynamic autocomplete depending on syntax and database objects
  LTextCompleter* completer = new LTextCompleter(highlighter->keyWords(), this);
  completer->setCaseSensitivity(Qt::CaseInsensitive);
  completer->setWidget(ui->teQueryEditor);
}

QueryEditorWindow::~QueryEditorWindow()
{
  delete ui;
}

void QueryEditorWindow::setStructureModel(QStructureItemModel *model)
{
  _model = model;
  _activeConnectionModel->setSourceModel(_model);
}

void QueryEditorWindow::on_aExecuteQuery_triggered()
{
  QSqlQuery query =
    QSqlDatabase::database(connectionName()).exec(ui->teQueryEditor->toPlainText());
  if (!query.lastError().isValid()){
    _resultModel->setQuery(query);
    ui->tabWidget->setCurrentWidget(ui->tabResult);
  }
  if (query.lastError().isValid()){
    ui->statusbar->showMessage(query.lastError().text());
  }
  else {
    if (query.isSelect())
      ui->statusbar->showMessage(QString::number(query.size()) + " rows selected");
    else
      ui->statusbar->showMessage(QString::number(query.numRowsAffected()) + " rows affected");
  }
}

QString QueryEditorWindow::connectionName()
{
  QModelIndex proxyIndex = _activeConnectionModel->index(ui->cmbDatabase->currentIndex(), 0);
  QModelIndex sourceIndex = _activeConnectionModel->mapToSource(proxyIndex);

  QDBObjectItem* databaseItem =
      (QDBObjectItem*)_model->itemByIndex(sourceIndex);
  return (databaseItem) ? databaseItem->connectionName() : "";
}

void QueryEditorWindow::on_aCommit_triggered()
{
  QSqlDatabase::database(connectionName()).commit();
}

void QueryEditorWindow::on_aRollback_triggered()
{
  QSqlDatabase::database(connectionName()).rollback();
}

void QueryEditorWindow::refreshConnectionList()
{
  _activeConnectionModel->invalidate();
}
