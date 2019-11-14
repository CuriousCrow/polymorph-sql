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

namespace Ui {
class QueryEditorWindow;
}

class QueryEditorWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit QueryEditorWindow(QWidget *parent = nullptr);
  ~QueryEditorWindow();

  void setStructureModel(QStructureItemModel* model);
  void refreshConnectionList();
  void refreshCompleterData();
private slots:
  void on_aExecuteQuery_triggered();

  void on_aCommit_triggered();

  void on_aRollback_triggered();

  void on_cmbDatabase_activated(const QString &arg1);

  void onHelpKey();
  void on_aExecScript_triggered();

private:
  Ui::QueryEditorWindow *ui;
  QStructureItemModel* _model;
  QActiveConnectionModel* _activeConnectionModel;
  QSqlQueryModel* _resultModel;
  LDBObjectModel* _compModel;
  QSqlSyntaxHighlighter* _highlighter;
  QSimpleTooltip* _helpTooltip;
  QString connectionName();
};

#endif // QUERYEDITORWINDOW_H
