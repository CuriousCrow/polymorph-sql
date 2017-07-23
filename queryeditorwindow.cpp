#include "queryeditorwindow.h"
#include "ui_queryeditorwindow.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardItemModel>
#include <QStandardItem>
#include "lqueryeditor.h"
#include "core/maphelplookupprovider.h"
#include "core/sqlhelplookupprovider.h"

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

  _highlighter = new QSqlSyntaxHighlighter(this);
  _highlighter->setDocument(ui->teQueryEditor->document());

  //Simple keywords autocompleter
  //TODO: Dynamic autocomplete depending on syntax and database objects
  _compModel = new LDBObjectModel(this);
  LTextCompleter* completer = new LTextCompleter(_compModel, this);
  completer->setCaseSensitivity(Qt::CaseInsensitive);
  completer->setWidget(ui->teQueryEditor);

//  MapHelpLookupProvider* helpProvider = new MapHelpLookupProvider(this);
//  helpProvider->addItem("SELECT", "<b>SELECT</b> is the most common keyword");
//  helpProvider->addItem("FROM", "FROM - is keyword used with SELECT clause");

  _helpTooltip = new QSimpleTooltip(this);
  _helpTooltip->setWidget(ui->teQueryEditor);
  _helpTooltip->setLookupProvider(new SqlHelpLookupProvider(this));

  LKeySequenceInterceptor* keyInterceptor = new LKeySequenceInterceptor(this);
  keyInterceptor->setKeySequence(QKeySequence(Qt::CTRL, Qt::Key_Q));
  keyInterceptor->applyToWidget(ui->teQueryEditor);
  connect(keyInterceptor, SIGNAL(keySequencePressed(QKeySequence)),
          this, SLOT(onHelpKey()));
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

void QueryEditorWindow::refreshCompleterData()
{
    _compModel->reload(_highlighter->keyWords(), connectionName());
}
void QueryEditorWindow::on_cmbDatabase_activated(const QString &arg1)
{
    refreshCompleterData();
}

void QueryEditorWindow::onHelpKey()
{
    qDebug() << "Help key!";
    _helpTooltip->popup(ui->teQueryEditor->currentWord(),
                        ui->teQueryEditor->cursorGlobalPos());
}

void QueryEditorWindow::on_aExecScript_triggered()
{
  int success = 0;
  int failed = 0;
  QStringList queries = ui->teQueryEditor->toPlainText().split(";");
  foreach(QString sql, queries) {
    QSqlQuery query =
        QSqlDatabase::database(connectionName()).exec(sql.trimmed());
    if (!query.lastError().isValid()){
      success++;
    }
    if (query.lastError().isValid()){
      failed++;
      qDebug() << "Error:" << query.lastError().text();
    }
  }
  ui->statusbar->showMessage("Succcess: " + QString::number(success) + ", Failed: " + QString::number(failed));
}
