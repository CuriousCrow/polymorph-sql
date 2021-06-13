#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include "sdk/models/lsqltablemodel.h"
#include "sdk/forms/connectioneditdialog.h"
#include <QMenu>
#include "sdk/models/qstructureitemmodel.h"
#include "queryeditorwindow.h"
#include "sdk/forms/tableeditform.h"
#include "sdk/forms/sequenceeditform.h"
#include "sdk/forms/procedureeditform.h"
#include "sdk/forms/vieweditdialog.h"
#include "sdk/forms/triggereditform.h"
#include "sdk/objects/dbtableitem.h"
#include "sdk/core/localeventnotifier.h"

#define MAIN_STATUS_BAR_TIMEOUT 5000

namespace Ui {
class MainWindow;
}

class MainWindow : public NotifiableWindow
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

  void exportCurrrentDatabaseObject();

  void exportCurrentDatabaseObjectData();

  void reloadItemChildren();

  void updateStructureContextMenu();

  void showCreateItemEditor();

  void saveDatabaseChanges();

  void saveObjectChanges();

  void on_aOpenSqlEditor_triggered();

  void on_aSettings_triggered();

  void on_aExportDatabase_triggered();

private:
  Ui::MainWindow *ui;
  ConnectionEditDialog* _connectionEditDialog;
  QMenu* _itemContextMenu;
  QMenu* _folderContextMenu;
  QAction* _editAction;
  QAction* _dropAction;
  QAction* _exportAction;
  QAction* _exportDataAction;
  QAction* _reloadAction;
  void addDatabase();
  DBObjectItem* itemByIndex(QModelIndex index);
  DBObjectItem* itemByName(QString name);
protected:
  //Dummy source change

  //Update connection comboboxes
  void refreshConnectionList();
  //Update object list for completer
  void refreshQueryEditorAssistance();

  void showItemInfoWidget(DBObjectItem* dbItem);
  void openTableEditor(DBSelectableItem* tableItem);

  // NotifiableWindow interface
protected:
  void localEvent(LocalEvent *event);
};

#endif // MAINWINDOW_H
