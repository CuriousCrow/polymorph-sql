#include "tablebrowserwindow.h"
#include "ui_tablebrowserwindow.h"
#include <QDebug>
#include <QMessageBox>
#include "dbms/appurl.h"
#include "dbms/appconst.h"

TableBrowserWindow::TableBrowserWindow(QWidget *parent, DBTableItem* tableItem) :
  QMainWindow(parent),
  ui(new Ui::TableBrowserWindow)
{
  qDebug() << "Connections:" << QSqlDatabase::connectionNames();
  ui->setupUi(this);
  AppUrl url = tableItem->objectUrl();
  setObjectName(url.toString());
  _connectionName = url.connection();
  _tableName = tableItem->fieldValue(F_CAPTION).toString();
  _sourceModel = new LSqlTableModel(this, QSqlDatabase::database(_connectionName));
  connect(_sourceModel, &LSqlTableModel::error,
          this, &TableBrowserWindow::onError);
  _sourceModel->setTable(_tableName);
  _sourceModel->select();
  _proxyModel = new QSortFilterProxyModel(this);
  _proxyModel->setSourceModel(_sourceModel);
  ui->tableView->setModel(_proxyModel);


  _mnuContext = new QMenu(this);
  _mnuContext->addAction(ui->aSetNull);
  _mnuContext->addSeparator();
  _mnuContext->addAction(ui->aEqualFilter);
  _mnuContext->addAction(ui->aNotEqualFilter);
  _mnuContext->addAction(ui->aGreaterThanFilter);
  _mnuContext->addAction(ui->aLessThanFilter);
  _mnuContext->addAction(ui->aFilterIsNull);
  _mnuContext->addAction(ui->aFilterIsNotNull);

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

void TableBrowserWindow::on_tableView_pressed(const QModelIndex &index)
{
  Q_UNUSED(index)
  if (QApplication::mouseButtons().testFlag(Qt::RightButton)) {
    _mnuContext->popup(QCursor::pos());
  }
}

void TableBrowserWindow::on_aSetNull_triggered()
{
  _sourceModel->setData(ui->tableView->currentIndex(), QVariant());
}

void TableBrowserWindow::onError(QString message)
{
  QMessageBox::warning(this, tr("Warning"), message);
}

void TableBrowserWindow::on_aResetFilters_triggered()
{
  _sourceModel->filter()->clear();
  _sourceModel->select();
}

void TableBrowserWindow::on_aEqualFilter_triggered()
{
  QString field = _sourceModel->fieldName(ui->tableView->currentIndex().column());
  QVariant value = ui->tableView->currentIndex().data();
  _sourceModel->filter()->addEqualFilter(field, value, false, WhereJoint::And);
  _sourceModel->select();
}

void TableBrowserWindow::on_aNotEqualFilter_triggered()
{
  QString field = _sourceModel->fieldName(ui->tableView->currentIndex().column());
  QVariant value = ui->tableView->currentIndex().data();
  _sourceModel->filter()->addEqualFilter(field, value, true, WhereJoint::And);
  _sourceModel->select();
}

void TableBrowserWindow::on_aGreaterThanFilter_triggered()
{
  QString field = _sourceModel->fieldName(ui->tableView->currentIndex().column());
  QVariant value = ui->tableView->currentIndex().data();
  _sourceModel->filter()->addMoreThanFilter(field, value, WhereJoint::And);
  _sourceModel->select();
}

void TableBrowserWindow::on_aLessThanFilter_triggered()
{
  QString field = _sourceModel->fieldName(ui->tableView->currentIndex().column());
  QVariant value = ui->tableView->currentIndex().data();
  _sourceModel->filter()->addLessThanFilter(field, value, WhereJoint::And);
  _sourceModel->select();
}

void TableBrowserWindow::on_aFilterIsNull_triggered()
{
  QString field = _sourceModel->fieldName(ui->tableView->currentIndex().column());
  _sourceModel->filter()->addNullFilter(field, false, WhereJoint::And);
  _sourceModel->select();
}

void TableBrowserWindow::on_aFilterIsNotNull_triggered()
{
  QString field = _sourceModel->fieldName(ui->tableView->currentIndex().column());
  _sourceModel->filter()->addNullFilter(field, true, WhereJoint::And);
  _sourceModel->select();
}
