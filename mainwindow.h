#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <lsqltablemodel.h>
#include "connectioneditdialog.h"
#include "vieweditdialog.h"
#include <QMenu>
#include "qstructureitemmodel.h"
#include "queryeditorwindow.h"
#include "vieweditdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_aAddDatabase_triggered();

  void on_aEditDatabase_triggered();

  void on_tvDatabaseStructure_doubleClicked(const QModelIndex &index);

  void on_tvDatabaseStructure_clicked(const QModelIndex &index);

  void removeTabByIndex(int index);

  void removeTabsByItemUrl(QString url);

  void on_aRemoveDatabase_triggered();

  void on_tvDatabaseStructure_pressed(const QModelIndex &index);

  void showEditorForCurrentItem();

  void dropCurrentDatabaseObject();
private:
  Ui::MainWindow *ui;
  QSqlDatabase appDB;
  QStructureItemModel* _structureModel;
  ConnectionEditDialog* _connectionEditDialog;
  QueryEditorWindow* _queryEditorWindow;
  ViewEditDialog* _viewEditorWindow;
  QMenu* _structureContextMenu;
  void addDatabase();
  QDBObjectItem* itemByIndex(QModelIndex index);
protected:
  //Dummy source change
};

#endif // MAINWINDOW_H
