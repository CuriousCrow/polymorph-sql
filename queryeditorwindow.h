#ifndef QUERYEDITORWINDOW_H
#define QUERYEDITORWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "qstructureitemmodel.h"
#include "qsqlsyntaxhighlighter.h"
#include "ltextcompleter.h"
#include "qactiveconnectionmodel.h"
#include "ldbobjectmodel.h"
#include "utils/qsimpletooltip.h"
#include "models/ldbobjecttablemodel.h"
#include "models/jointdbojbectmodel.h"
#include "models/queryparamtablemodel.h"
#include "forms/queryparamsform.h"
#include "core/datastore.h"

#define STATUS_BAR_TIMEOUT 5000

namespace Ui {
class QueryEditorWindow;
}

class QueryEditorWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit QueryEditorWindow(QWidget *parent = nullptr);
  ~QueryEditorWindow();
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
  QActiveConnectionModel* _activeConnectionModel;
  QSqlQueryModel* _resultModel;
//  LDBObjectModel* _compModel;
  JointDBOjbectModel* _knowledgeModel;
  LDBObjectTableModel* _objectsModel;
  QSqlSyntaxHighlighter* _highlighter;
  LTextCompleter* _completer;
  QSimpleTooltip* _helpTooltip;
  QString connectionName();
  QString dbUrl();
  DBObjectItem* dbObject();
  QString aliasSource(QString alias);
  QString getActiveText();
  QString generateAlias(QString tableName);
  QString _lastExecutedQuery;
};

#endif // QUERYEDITORWINDOW_H
