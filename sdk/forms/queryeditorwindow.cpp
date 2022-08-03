#include "queryeditorwindow.h"
#include "ui_queryeditorwindow.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardItemModel>
#include <QStandardItem>
#include "widgets/lqueryeditor.h"
#include "core/maphelplookupprovider.h"
#include "core/localeventnotifier.h"
#include "objects/sdkplugin.h"
#include "objects/appconst.h"
#include "queryhistoryform.h"
#include "utils/messagedialogs.h"



#include <QComboBox>

#include <QStringListModel>

QueryEditorWindow::QueryEditorWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::QueryEditorWindow)
{
  ui->setupUi(this);

  _resultModel = new QSqlQueryModel(this);
  ui->tvResultSet->setModel(_resultModel);

  _keyInterceptor = new KeySequenceInterceptor(this);
  _keyInterceptor->attachToWidget(ui->teQueryEditor);

  _extensionPoints.insert(ExtensionPoint(EP_QUERYEDITOR_KEYSEQUENCE, CLASS(AbstractKeySequenceHandler), "Test key sequence handler", false));

  connect(ui->cmbDatabase, SIGNAL(currentIndexChanged(int)),
          this, SLOT(reloadKnowledgeModel()));

  _activeConnectionModel = new LActiveConnectionModel(this);

  _helpTooltip = new LSimpleTooltip(this);
  _helpTooltip->setOpenExternalLinks(true);
  _helpTooltip->setWidget(ui->teQueryEditor);

  LKeySequenceInterceptor* keyInterceptor = new LKeySequenceInterceptor(this);
  keyInterceptor->setKeySequence(QKeySequence(Qt::CTRL, Qt::Key_Q));
  keyInterceptor->applyToWidget(ui->teQueryEditor);
  connect(keyInterceptor, SIGNAL(keySequencePressed(QKeySequence)),
          this, SLOT(onHelpKey()));

  connect(ui->teQueryEditor, &LQueryEditor::wordClicked,
          this, &QueryEditorWindow::onFindObject);

  connect(ui->teQueryEditor, &LQueryEditor::infoMessage,
          this, &QueryEditorWindow::updateStatusMessage);
}

QueryEditorWindow::~QueryEditorWindow()
{
  qDebug() << "Query editor destructor";
  delete ui;
}

void QueryEditorWindow::inject_by_ds(DataStore *ds)
{
  qDebug() << "QueryEditorWindow: Inject DataStore singleton";
  _ds = ds;
  _activeConnectionModel->setSourceModel(_ds->structureModel());
  ui->cmbDatabase->setModel(_activeConnectionModel);
  ui->cmbDatabase->setModelColumn(0);
}

void QueryEditorWindow::inject_helpLookupProvider(SqlHelpLookupProvider *lookupProvider)
{
  _helpLookupProvider = lookupProvider;
  _helpTooltip->setLookupProvider(_helpLookupProvider);
}

void QueryEditorWindow::inject_by_sqlSyntaxHighlighter(LSqlSyntaxHighlighter *syntaxHighlighter)
{
    _highlighter = syntaxHighlighter;
    _highlighter->setDocument(ui->teQueryEditor->document());
}

void QueryEditorWindow::inject_sqlCompleterSupport_into_form(SimpleSqlCompleterSupport *completerSupport)
{
  _completerSupport = completerSupport;
  _completerSupport->setParent(this);
  _completerSupport->setWidget(ui->teQueryEditor);
}

void QueryEditorWindow::on_aExecuteQuery_triggered()
{
  if (ui->cmbDatabase->currentIndex() < 0) {
      updateStatusMessage(tr("Database need to be selected"));
      return;
  }
  QString text = getActiveText();
  if (text.contains(";")) {
    MessageDialogs::warn(tr("Please, select only one SQL-query or use \"Run Scripts\" action"));
    return;
  }

  QSqlQuery query = SqlQueryHelper::execSql(text, connectionName());
  if (!query.lastError().isValid()){
    _resultModel->setQuery(query);
    ui->tabWidget->setCurrentWidget(ui->tabResult);
  }
  if (query.lastError().isValid()){
    updateStatusMessage(query.lastError().text());
  }
  else {
    if (query.isSelect())
      updateStatusMessage(QString::number(query.size()) + " rows selected");
    else
      updateStatusMessage(QString::number(query.numRowsAffected()) + " rows affected");
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

DBDatabaseItem *QueryEditorWindow::dbObject()
{
  QModelIndex proxyIndex = _activeConnectionModel->index(ui->cmbDatabase->currentIndex(), 0);
  QModelIndex sourceIndex = _activeConnectionModel->mapToSource(proxyIndex);

  return static_cast<DBDatabaseItem*>(_ds->structureModel()->itemByIndex(sourceIndex));
}

QString QueryEditorWindow::getActiveText()
{
  QString activeText = ui->teQueryEditor->textCursor().selectedText();
  if (activeText.isEmpty())
    activeText = ui->teQueryEditor->toPlainText();
  activeText = ui->paramsForm->applyParams(activeText);
  if (_lastExecutedQuery != activeText) {
    qDebug() << "New query registered in history:" << activeText;
    _ds->addQueryHistoryItem(ui->cmbDatabase->currentData().toInt(), activeText);
    _lastExecutedQuery = activeText;
  }
  return activeText;
}

void QueryEditorWindow::reloadKnowledgeModel()
{
  DBDatabaseItem* dbItem = dbObject();
  _completerSupport->setDatabaseItem(dbItem);
  _helpLookupProvider->updateHelpModels(dbItem->driverName());
  _highlighter->updateModels(dbItem->driverName());
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

void QueryEditorWindow::onHelpKey()
{
  _helpTooltip->popup(ui->teQueryEditor->currentWord(),
                      ui->teQueryEditor->cursorGlobalPos());
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
  updateStatusMessage("Succcess: " + QString::number(success) + ", Failed: " + QString::number(failed));
}

void QueryEditorWindow::onFindObject(QString word, Qt::KeyboardModifiers modifiers)
{
  if (!modifiers.testFlag(Qt::ControlModifier))
    return;
  QVariantMap dbObj = _completerSupport->objectsModel()->rowByName(word);
  //If current word is a table/view name then open table browser
  if (!dbObj.isEmpty()) {
    if (dbObj.value(F_TYPE).toString() == OBJTYPE_TABLE) {
      QString url = dbUrl() + DELIMITER + FOLDER_TABLES + DELIMITER + word;
      LocalEventNotifier::postLocalEvent(ShowObjectEvent, url);
    }
    else if (dbObj.value(F_TYPE).toString() == OBJTYPE_VIEW) {
      QString url = dbUrl() + DELIMITER + FOLDER_VIEWS + DELIMITER + word;
      LocalEventNotifier::postLocalEvent(ShowObjectEvent, url);
    }
  }
}

void QueryEditorWindow::on_aQueryHistory_triggered()
{
  DBDatabaseItem* dbObj = dynamic_cast<DBDatabaseItem*>(dbObject());
  if (dbObj) {
    QueryHistoryForm* historyForm = _core->dependency<QueryHistoryForm>(B_QUERY_HISTORY_FORM);
    historyForm->loadHistory(dbObj->fieldValue(F_ID).toInt());
    connect(historyForm, &QueryHistoryForm::accepted,
            this, &QueryEditorWindow::onHistoryClosed);
    historyForm->setModal(true);
    historyForm->show();
  }
}

void QueryEditorWindow::onHistoryClosed()
{
  QueryHistoryForm* historyForm = static_cast<QueryHistoryForm*>(sender());
  if (historyForm->result()) {
    ui->teQueryEditor->setPlainText(historyForm->selectedQuery());
  }
}

void QueryEditorWindow::updateStatusMessage(const QString &message)
{
    ui->statusbar->showMessage(message, STATUS_BAR_TIMEOUT);
}

void QueryEditorWindow::on_aUpdateParams_triggered()
{
    QRegularExpression rxParam("#([A-Za-z]+)#");
    QString text = ui->teQueryEditor->toPlainText();
    QVariantMap paramMap;
    QRegularExpressionMatchIterator i = rxParam.globalMatch(text);
    while(i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString paramName = match.captured(1);
        qDebug() << paramName;
        paramMap.insert(paramName, "");
    }
    ui->paramsForm->setParams(paramMap);
}

void QueryEditorWindow::injectExtension(ExtensionPoint ep, QObject *e)
{
  qDebug() << "Inject QueryEditor extension:" << e->objectName();
  if (e->inherits(CLASS(AbstractKeySequenceHandler))) {
    if (ep.name() == EP_QUERYEDITOR_KEYSEQUENCE) {
      AbstractKeySequenceHandler* keyHander = static_cast<AbstractKeySequenceHandler*>(e);
      if (e->inherits(CLASS(QueryEditorKeyHandler))) {
        QueryEditorKeyHandler* editorKeyHandler = static_cast<QueryEditorKeyHandler*>(e);
        editorKeyHandler->setEditor(ui->teQueryEditor);
      }
      _keyInterceptor->registerHandler(keyHander);
    }
  }
}
