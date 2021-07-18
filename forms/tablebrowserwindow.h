#ifndef TABLEBROWSERWINDOW_H
#define TABLEBROWSERWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QMenu>
#include "sdk/models/unisqltablemodel.h"
#include <QSortFilterProxyModel>
#include "sdk/objects/dbtableitem.h"

namespace Ui {
class TableBrowserWindow;
}

class TableBrowserWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit TableBrowserWindow(QWidget *parent, DBSelectableItem* tableItem);
  ~TableBrowserWindow();

private slots:
  void on_aSubmit_triggered();

  void on_aRevert_triggered();

  void on_aAddRow_triggered();

  void on_aDeleteRow_triggered();

  void on_aRefresh_triggered();

  void on_tableView_pressed(const QModelIndex &index);

  void on_aSetNull_triggered();

  void onError(QString message);

  void on_aResetFilters_triggered();

  void on_aEqualFilter_triggered();

  void on_aNotEqualFilter_triggered();

  void on_aGreaterThanFilter_triggered();

  void on_aLessThanFilter_triggered();

  void on_aFilterIsNull_triggered();

  void on_aFilterIsNotNull_triggered();

  void on_aRemoveFilter_triggered();

  void on_lvFilters_pressed(const QModelIndex &index);

  void onCurrentItemChanged(const QModelIndex &index);

  void on_aLoadFromFile_triggered();

  void on_aTest_triggered();

  void onColumnVisibilityActionToggled(bool checked);

  void onHeaderPressed();
private:
  Ui::TableBrowserWindow *ui;
  QString _tableName;
  QString _connectionName;
  UniSqlTableModel* _sourceModel;
  QSortFilterProxyModel* _proxyModel;
  DBSelectableItem* _tableItem;
  QMenu* _mnuContext;
  QMenu* _mnuFilterList;
  QMenu* _mnuColumns;
  void refreshColumnsMenu();
  void refreshTable();
  void loadColumnsState();
};

#endif // TABLEBROWSERWINDOW_H
