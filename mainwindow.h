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
#include "forms/tableeditform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
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

  void updateStructureContextMenu();

  void showCreateItemEditor();

  void saveTableChanges();
  void on_aOpenSqlEditor_triggered();

private:
  Ui::MainWindow *ui;
  QSqlDatabase appDB;
  QStructureItemModel* _structureModel;
  ConnectionEditDialog* _connectionEditDialog;
  ViewEditDialog* _viewEditorWindow;
  TableEditForm* _tableEditForm;
  QMenu* _itemContextMenu;
  QMenu* _folderContextMenu;
  QAction* _editAction;
  QAction* _dropAction;
  void addDatabase();
  QDBObjectItem* itemByIndex(QModelIndex index);
protected:
  //Dummy source change

  //Update connection comboboxes
  void refreshConnectionList();
  //Update object list for completer
  void refreshQueryEditorAssistance();
};

#endif // MAINWINDOW_H
