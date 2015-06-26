#ifndef QUERYEDITORWINDOW_H
#define QUERYEDITORWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "qstructureitemmodel.h"
#include "qsqlsyntaxhighlighter.h"
#include "ltextcompleter.h"
#include "qactiveconnectionmodel.h"

namespace Ui {
class QueryEditorWindow;
}

class QueryEditorWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit QueryEditorWindow(QWidget *parent = 0);
  ~QueryEditorWindow();

  void setStructureModel(QStructureItemModel* model);
  void refreshConnectionList();
private slots:
  void on_aExecuteQuery_triggered();

  void on_aCommit_triggered();

  void on_aRollback_triggered();

private:
  Ui::QueryEditorWindow *ui;
  QStructureItemModel* _model;
  QActiveConnectionModel* _activeConnectionModel;
  QSqlQueryModel* _resultModel;
  QString connectionName();
};

#endif // QUERYEDITORWINDOW_H
