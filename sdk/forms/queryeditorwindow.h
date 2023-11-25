#ifndef QUERYEDITORWINDOW_H
#define QUERYEDITORWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "core/datastore.h"
#include "core/core.h"
#include "core/lknowledgebase.h"
#include "core/dependencycontainer.h"
#include "models/lactiveconnectionmodel.h"
#include "models/lsqlquerymodel.h"
#include "tools/sqleditorsupport.h"

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
  INJECT(SqlEditorSupport*, editorSupport);
  Q_INVOKABLE void inject_by_ds(DataStore* ds);

public slots:
  void refreshConnectionList();
  void reloadKnowledgeModel();
private slots:
  void on_aExecuteQuery_triggered();
  void on_aCommit_triggered();
  void on_aRollback_triggered();

  void on_aExecScript_triggered();
  void onFindObject(QString word, Qt::KeyboardModifiers modifiers);
  void on_aQueryHistory_triggered();
  void onHistoryClosed();
  void updateStatusMessage(const QString &message);

  void on_aUpdateParams_triggered();

private:
  Ui::QueryEditorWindow *ui;
  LActiveConnectionModel* _activeConnectionModel;
  LSqlQueryModel* _resultModel;
  DataStore* _ds;
  QString connectionName();
  QString dbUrl();
  DBDatabaseItem* dbObject();
  QString getActiveText();
  QString _lastExecutedQuery;
};

#endif // QUERYEDITORWINDOW_H
