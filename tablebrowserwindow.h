#ifndef TABLEBROWSERWINDOW_H
#define TABLEBROWSERWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include "dbms/qdbtableitem.h"

namespace Ui {
class TableBrowserWindow;
}

class TableBrowserWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit TableBrowserWindow(QWidget *parent, QDBTableItem* tableItem);
  ~TableBrowserWindow();

private slots:
  void on_aSubmit_triggered();

  void on_aRevert_triggered();

  void on_aAddRow_triggered();

  void on_aDeleteRow_triggered();

  void on_aRefresh_triggered();

private:
  Ui::TableBrowserWindow *ui;
  QString _tableName;
  QString _connectionName;
  QSqlTableModel* _sourceModel;
  QSortFilterProxyModel* _proxyModel;
};

#endif // TABLEBROWSERWINDOW_H
