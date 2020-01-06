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
#include "core/localeventnotifier.h"
#include "dbms/appconst.h"
#include <QComboBox>

QueryEditorWindow::QueryEditorWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::QueryEditorWindow)
{
  ui->setupUi(this);

  _resultModel = new QSqlQueryModel(this);
  ui->tvResultSet->setModel(_resultModel);

  //Simple keywords autocompleter
  //TODO: Dynamic autocomplete depending on syntax and database objects
  _compModel = new LDBObjectModel(this);
  LTextCompleter* completer = new LTextCompleter(_compModel, this);
  QTableView* completerView = new QTableView(this);
  completerView->horizontalHeader()->hide();
  completerView->verticalHeader()->hide();
  completerView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  completer->setPopup(completerView);
  completer->setCaseSensitivity(Qt::CaseInsensitive);
  completer->setWidget(ui->teQueryEditor);

  _highlighter = new QSqlSyntaxHighlighter(this);
  _highlighter->setDocument(ui->teQueryEditor->document());

  connect(ui->cmbDatabase, SIGNAL(currentIndexChanged(int)),
          this, SLOT(refreshCompleterData()));

  _activeConnectionModel = new QActiveConnectionModel(this);
  _activeConnectionModel->setSourceModel(DataStore::structureModel());
  ui->cmbDatabase->setModel(_activeConnectionModel);
  ui->cmbDatabase->setModelColumn(0);

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

  LKeySequenceInterceptor* aliasInterceptor = new LKeySequenceInterceptor(this);
  aliasInterceptor->setKeySequence(QKeySequence(Qt::CTRL, Qt::Key_T));
  aliasInterceptor->applyToWidget(ui->teQueryEditor);
  connect(aliasInterceptor, SIGNAL(keySequencePressed(QKeySequence)),
          this, SLOT(onAddAlias()));


  connect(ui->teQueryEditor, SIGNAL(wordClicked(QString, Qt::KeyboardModifiers)),
          this, SLOT(onFindObject(QString, Qt::KeyboardModifiers)));
}

QueryEditorWindow::~QueryEditorWindow()
{
  qDebug() << "Query editor destructor";
  delete ui;
}

void QueryEditorWindow::on_aExecuteQuery_triggered()
{
  QSqlQuery query =
      QSqlDatabase::database(connectionName()).exec(getActiveText());
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
  DBObjectItem* databaseItem = dbObject();
  return (databaseItem) ? databaseItem->connectionName() : "";
}

QString QueryEditorWindow::dbUrl()
{
  return dbObject()->objectUrl().toString();
}

DBObjectItem *QueryEditorWindow::dbObject()
{
  QModelIndex proxyIndex = _activeConnectionModel->index(ui->cmbDatabase->currentIndex(), 0);
  QModelIndex sourceIndex = _activeConnectionModel->mapToSource(proxyIndex);

  return qobject_cast<DBObjectItem*>(DataStore::structureModel()->itemByIndex(sourceIndex));
}

QString QueryEditorWindow::getActiveText()
{
  QString activeText = ui->teQueryEditor->textCursor().selectedText();
  if (activeText.isEmpty())
    activeText = ui->teQueryEditor->toPlainText();
  return activeText;
}

QString QueryEditorWindow::generateAlias(QString tableName)
{
//  qDebug() << "Table name: " << tableName;
  QStringList sl = tableName.split("_", QString::SkipEmptyParts);
  QString alias;
  foreach(QString word, sl) {
    alias += word.at(0).toLower();
  }
  return alias;
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
  qDebug() << "Refilter connection list";
  _activeConnectionModel->invalidate();
}

void QueryEditorWindow::refreshCompleterData()
{
  _compModel->reload(_highlighter->keyWords(), connectionName());
}

void QueryEditorWindow::onHelpKey()
{
  _helpTooltip->popup(ui->teQueryEditor->currentWord(),
                      ui->teQueryEditor->cursorGlobalPos());
}

void QueryEditorWindow::onAddAlias()
{
  QString curWord = ui->teQueryEditor->currentWord();
  QString prevWord = ui->teQueryEditor->previousWord();

  QString tableAlias = generateAlias(curWord.isEmpty() ? prevWord : curWord);
  if (!curWord.isEmpty())
    ui->teQueryEditor->textCursor().insertText(" ");
  ui->teQueryEditor->textCursor().insertText(tableAlias);
}

void QueryEditorWindow::on_aExecScript_triggered()
{
  int success = 0;
  int failed = 0;
  QStringList queries = getActiveText().split(";");
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

void QueryEditorWindow::onFindObject(QString word, Qt::KeyboardModifiers modifiers)
{
  if (!modifiers.testFlag(Qt::ControlModifier))
    return;
  DbObj dbObj = _compModel->findByName(word);
  //If current word is a table/view name then open table browser
  if (dbObj.isValid()) {
    if (dbObj.type == OBJTYPE_TABLE) {
      QString url = dbUrl() + DELIMITER + FOLDER_TABLES + DELIMITER + dbObj.name;
      LocalEventNotifier::postLocalEvent(ShowObjectEvent, url);
    }
    else if (dbObj.type == OBJTYPE_VIEW) {
      QString url = dbUrl() + DELIMITER + FOLDER_VIEWS + DELIMITER + dbObj.name;
      LocalEventNotifier::postLocalEvent(ShowObjectEvent, url);
    }
  }
}
