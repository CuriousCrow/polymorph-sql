#include "tablebrowserwindow.h"
#include "ui_tablebrowserwindow.h"
#include <QDebug>
#include <QUrl>

TableBrowserWindow::TableBrowserWindow(QWidget *parent, QDBTableItem* tableItem) :
  QMainWindow(parent),
  ui(new Ui::TableBrowserWindow)
{
  ui->setupUi(this);
  QUrl url = tableItem->objectUrl();
  setObjectName(url.url());
  _connectionName = url.host();
  _tableName = tableItem->caption();
  _sourceModel = new QSqlTableModel(this, QSqlDatabase::database(_connectionName));
  _sourceModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
  _sourceModel->setTable(_tableName);
  _sourceModel->select();
  _proxyModel = new QSortFilterProxyModel(this);
  _proxyModel->setSourceModel(_sourceModel);
  ui->tableView->setModel(_proxyModel);
  qDebug() << "TableBrowserWindow" << objectName() << "created";
}

TableBrowserWindow::~TableBrowserWindow()
{
  qDebug() << "TableBrowserWindow" << objectName() << "destroyed";
  delete ui;
}

void TableBrowserWindow::on_aSubmit_triggered()
{
  _sourceModel->submitAll();
}

void TableBrowserWindow::on_aRevert_triggered()
{
  _sourceModel->revertAll();
}

void TableBrowserWindow::on_aAddRow_triggered()
{
  _sourceModel->insertRow(_sourceModel->rowCount());
}

void TableBrowserWindow::on_aDeleteRow_triggered()
{
  QModelIndex index = ui->tableView->currentIndex();
  if (!index.isValid())
    return;
  _sourceModel->removeRow(index.row());
}

void TableBrowserWindow::on_aRefresh_triggered()
{
  //in case the table structure has changed
  _sourceModel->setTable(_sourceModel->tableName());
  //get actual table data
  _sourceModel->select();
}
