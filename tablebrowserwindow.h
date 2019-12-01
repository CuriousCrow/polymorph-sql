#ifndef TABLEBROWSERWINDOW_H
#define TABLEBROWSERWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QMenu>
#include "lsqltablemodel.h"
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

private:
  Ui::TableBrowserWindow *ui;
  QString _tableName;
  QString _connectionName;
  LSqlTableModel* _sourceModel;
  QSortFilterProxyModel* _proxyModel;
  QMenu* _mnuContext;
};

#endif // TABLEBROWSERWINDOW_H
