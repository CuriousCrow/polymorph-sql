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
#include "core/datastore.h"

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
  void refreshCompleterData();
private slots:
  void on_aExecuteQuery_triggered();

  void on_aCommit_triggered();

  void on_aRollback_triggered();

  void onHelpKey();
  void onAddAlias();
  void on_aExecScript_triggered();
  void onFindObject(QString word, Qt::KeyboardModifiers modifiers);
  void onCompleterRequested(const QString &contextText);
private:
  Ui::QueryEditorWindow *ui;
  QActiveConnectionModel* _activeConnectionModel;
  QSqlQueryModel* _resultModel;
  LDBObjectModel* _compModel;
  QSqlSyntaxHighlighter* _highlighter;
  LTextCompleter* _completer;
  QSimpleTooltip* _helpTooltip;
  QString connectionName();
  QString dbUrl();
  DBObjectItem* dbObject();
  QString aliasSource(QString alias);
  QString getActiveText();
  QString generateAlias(QString tableName);
};

#endif // QUERYEDITORWINDOW_H
