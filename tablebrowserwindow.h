#ifndef TABLEBROWSERWINDOW_H
#define TABLEBROWSERWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>

namespace Ui {
class TableBrowserWindow;
}

class TableBrowserWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit TableBrowserWindow(QWidget *parent, QSqlDatabase db, QString table);
  ~TableBrowserWindow();

private:
  Ui::TableBrowserWindow *ui;
  QString table;
  QSqlDatabase db;
  QSqlTableModel* sourceModel;
  QSortFilterProxyModel* proxyModel;
};

#endif // TABLEBROWSERWINDOW_H
