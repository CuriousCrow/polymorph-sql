#include "tablebrowserwindow.h"
#include "ui_tablebrowserwindow.h"

TableBrowserWindow::TableBrowserWindow(QWidget *parent, QSqlDatabase db, QString table) :
  QMainWindow(parent),
  ui(new Ui::TableBrowserWindow)
{
  ui->setupUi(this);
  this->db = db;
  this->table = table;
  sourceModel = new QSqlTableModel(this, db);
  sourceModel->setTable(table);
  sourceModel->select();
  proxyModel = new QSortFilterProxyModel(this);
  proxyModel->setSourceModel(sourceModel);
  ui->tableView->setModel(proxyModel);
}

TableBrowserWindow::~TableBrowserWindow()
{
  delete ui;
}
