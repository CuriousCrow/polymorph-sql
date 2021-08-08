#ifndef QUERYEDITORWINDOW_H
#define QUERYEDITORWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "sdk/models/lstructureitemmodel.h"
#include "sdk/tools/lsqlsyntaxhighlighter.h"
#include "sdk/tools/ltextcompleter.h"
#include "sdk/models/lactiveconnectionmodel.h"
#include "sdk/models/ldbobjectmodel.h"
#include "sdk/utils/lsimpletooltip.h"
#include "sdk/models/ldbobjecttablemodel.h"
#include "sdk/models/jointdbojbectmodel.h"
#include "sdk/models/queryparamtablemodel.h"
#include "sdk/forms/queryparamsform.h"
#include "sdk/core/datastore.h"
#include "sdk/core/lknowledgebase.h"
#include "core/dependencycontainer.h"
#include "sdk/core/sqlhelplookupprovider.h"

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
  Q_INVOKABLE void inject_by_ds(DataStore* ds);
  Q_INVOKABLE void inject_helpLookupProvider(SqlHelpLookupProvider* lookupProvider);
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
  void onCompleterRequested(const QString &contextText);
  void on_aQueryHistory_triggered();
  void onHistoryClosed();
  void updateStatusMessage(const QString &message);

  void on_aUpdateParams_triggered();

private:
  Ui::QueryEditorWindow *ui;
  LActiveConnectionModel* _activeConnectionModel;
  QSqlQueryModel* _resultModel;
  DataStore* _ds;
//  LDBObjectModel* _compModel;
  JointDBOjbectModel* _knowledgeModel;
  LDBObjectTableModel* _objectsModel;
  LSqlSyntaxHighlighter* _highlighter;
  LTextCompleter* _completer;
  LSimpleTooltip* _helpTooltip;
  QString connectionName();
  QString dbUrl();
  DBObjectItem* dbObject();
  QString aliasSource(QString alias);
  QString getActiveText();
  QString generateAlias(QString tableName);
  QString _lastExecutedQuery;
};

#endif // QUERYEDITORWINDOW_H
