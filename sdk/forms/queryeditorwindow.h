#ifndef QUERYEDITORWINDOW_H
#define QUERYEDITORWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "models/lstructureitemmodel.h"
#include "tools/lsqlsyntaxhighlighter.h"
#include "tools/ltextcompleter.h"
#include "models/lactiveconnectionmodel.h"
#include "models/ldbobjectmodel.h"
#include "utils/lsimpletooltip.h"
#include "models/ldbobjecttablemodel.h"
#include "models/jointdbojbectmodel.h"
#include "models/queryparamtablemodel.h"
#include "forms/queryparamsform.h"
#include "core/datastore.h"
#include "core/core.h"
#include "core/lknowledgebase.h"
#include "core/dependencycontainer.h"
#include "core/sqlhelplookupprovider.h"
#include "tools/simplesqlcompletersupport.h"

#define STATUS_BAR_TIMEOUT 5000

namespace Ui {
class QueryEditorWindow;
}

class QueryEditorWindow : public QMainWindow
{
  Q_OBJECT

public:
  Q_INVOKABLE QueryEditorWindow(QWidget *parent = nullptr);
  ~QueryEditorWindow();

  INJECT(LKnowledgeBase*, kb)
  INJECT(Core*, core)
  Q_INVOKABLE void inject_sqlCompleterSupport_into_form(SimpleSqlCompleterSupport* completerSupport);
  Q_INVOKABLE void inject_by_ds(DataStore* ds);
  Q_INVOKABLE void inject_helpLookupProvider(SqlHelpLookupProvider* lookupProvider);
  Q_INVOKABLE void inject_by_sqlSyntaxHighlighter(LSqlSyntaxHighlighter* syntaxHighlighter);

public slots:
  void refreshConnectionList();
  void reloadKnowledgeModel();
private slots:
  void on_aExecuteQuery_triggered();

  void on_aCommit_triggered();

  void on_aRollback_triggered();

  void onHelpKey();
  void onAddAlias();
  void on_aExecScript_triggered();
  void onFindObject(QString word, Qt::KeyboardModifiers modifiers);
  void on_aQueryHistory_triggered();
  void onHistoryClosed();
  void updateStatusMessage(const QString &message);

  void on_aUpdateParams_triggered();

private:
  Ui::QueryEditorWindow *ui;
  LActiveConnectionModel* _activeConnectionModel;
  QSqlQueryModel* _resultModel;
  DataStore* _ds;
  SimpleSqlCompleterSupport* _completerSupport;
  LSqlSyntaxHighlighter* _highlighter;
  LSimpleTooltip* _helpTooltip;
  QString connectionName();
  QString dbUrl();
  DBDatabaseItem* dbObject();
  QString getActiveText();
  QString generateAlias(QString tableName);
  QString _lastExecutedQuery;
};

#endif // QUERYEDITORWINDOW_H
