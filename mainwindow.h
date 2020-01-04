#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <lsqltablemodel.h>
#include "connectioneditdialog.h"
#include <QMenu>
#include "qstructureitemmodel.h"
#include "queryeditorwindow.h"
#include "forms/tableeditform.h"
#include "forms/sequenceeditform.h"
#include "forms/procedureeditform.h"
#include "forms/vieweditdialog.h"
#include "forms/triggereditform.h"
#include "dbms/dbtableitem.h"
#include "core/localeventnotifier.h"

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

  void reloadItemChildren();

  void updateStructureContextMenu();

  void showCreateItemEditor();

  void saveTableChanges();

  void saveViewChanges();

  void saveSequenceChanges();

  void saveProcedureChanges();

  void saveTriggerChanges();

  void on_aOpenSqlEditor_triggered();

private:
  Ui::MainWindow *ui;
  ConnectionEditDialog* _connectionEditDialog;
  ViewEditDialog* _viewEditorWindow;
  TableEditForm* _tableEditForm;
  ProcedureEditForm* _procedureEditForm;
  SequenceEditForm* _sequenceEditForm;
  TriggerEditForm* _triggerEditForm;
  QMenu* _itemContextMenu;
  QMenu* _folderContextMenu;
  QAction* _editAction;
  QAction* _dropAction;
  QAction* _reloadAction;
  void addDatabase();
  DBObjectItem* itemByIndex(QModelIndex index);
  DBObjectItem* itemByName(QString name);

  QString typeName(DBObjectItem::ItemType type);
protected:
  //Dummy source change

  //Update connection comboboxes
  void refreshConnectionList();
  //Update object list for completer
  void refreshQueryEditorAssistance();

  void showItemInfoWidget(DBObjectItem* dbItem);
  void openTableEditor(DBTableItem* tableItem);

  // NotifiableWindow interface
protected:
  void localEvent(LocalEvent *event);
};

#endif // MAINWINDOW_H
