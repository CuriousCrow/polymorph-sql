#ifndef TABLEBROWSERWINDOW_H
#define TABLEBROWSERWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QMenu>
#include "models/unisqltablemodel.h"
#include <QSortFilterProxyModel>
#include "dbms/dbtableitem.h"

namespace Ui {
class TableBrowserWindow;
}

class TableBrowserWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit TableBrowserWindow(QWidget *parent, DBTableItem* tableItem);
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

private:
  Ui::TableBrowserWindow *ui;
  QString _tableName;
  QString _connectionName;
  UniSqlTableModel* _sourceModel;
  QSortFilterProxyModel* _proxyModel;
  DBTableItem* _tableItem;
  QMenu* _mnuContext;
  QMenu* _mnuFilterList;

};

#endif // TABLEBROWSERWINDOW_H
