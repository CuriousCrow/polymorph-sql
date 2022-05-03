#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QMenu>
#include "sdk/models/lsqltablemodel.h"
#include "sdk/forms/connectioneditdialog.h"
#include "sdk/models/lstructureitemmodel.h"
#include "sdk/core/localeventnotifier.h"
#include "sdk/core/baseusercontext.h"
#include "sdk/core/datastore.h"
#include "sdk/core/core.h"
#include "sdk/core/lknowledgebase.h"
#include "core/extensionpoints.h"
#include "core/extensions.h"

#define MAIN_STATUS_BAR_TIMEOUT 5000

namespace Ui {
class MainWindow;
}

class MainWindow : public NotifiableWindow, public Extensible
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_aAddDatabase_triggered();

  void on_aEditDatabase_triggered();

  void on_tvDatabaseStructure_doubleClicked(const QModelIndex &index);

  void removeTabByIndex(int index);

  void removeTabsByItemUrl(QString url);

  void on_aRemoveDatabase_triggered();

  void on_tvDatabaseStructure_pressed(const QModelIndex &index);

  void showEditorForCurrentItem();

  void dropCurrentDatabaseObject();

  void saveDatabaseChanges();

  void saveObjectChanges();

  void onCurrentItemChanged(const QModelIndex &index);

private:
  Ui::MainWindow *ui;
  DataStore* _ds;
  Core* _core;
  LKnowledgeBase* _kb;
  BaseUserContext* _context;
  ConnectionEditDialog* _connectionEditDialog;
  QMenu* _itemContextMenu;
  void addDatabase();
  DBObjectItem* itemByIndex(QModelIndex index);
  DBObjectItem* itemByName(QString name);
protected:
  //Update connection comboboxes
  void refreshConnectionList();
  //Update object list for completer
  void refreshQueryEditorAssistance(DBObjectItem* item);

  void showItemInfoWidget(DBObjectItem* dbItem);
  void openTableEditor(DBSelectableItem* tableItem);

  // NotifiableWindow interface
protected:
  void localEvent(LocalEvent *event) override;

  // Extensible interface
public:
  virtual void injectExtension(ExtensionPoint ep, QObject *e) override;
};

#endif // MAINWINDOW_H
