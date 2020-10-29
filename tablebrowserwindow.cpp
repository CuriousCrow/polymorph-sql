#include "tablebrowserwindow.h"
#include "ui_tablebrowserwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include "dbms/appconst.h"
#include "dbms/appurl.h"
#include "dbms/appconst.h"
#include "utils/qfileutils.h"
#include "core/datastore.h"
#include "tablebrowserdelegate.h"

TableBrowserWindow::TableBrowserWindow(QWidget *parent, DBTableItem* tableItem) :
  QMainWindow(parent),
  ui(new Ui::TableBrowserWindow),
  _tableItem(tableItem)
{
  qDebug() << "Connections:" << QSqlDatabase::connectionNames();
  ui->setupUi(this);

  _tableItem->reloadColumnsModel();
  _tableItem->reloadConstraintsModel();

  AppUrl url = _tableItem->objectUrl();
  setObjectName(url.toString());
  _connectionName = url.connection();
  _tableName = _tableItem->fieldValue(F_CAPTION).toString();
  _sourceModel = new UniSqlTableModel(this, QSqlDatabase::database(_connectionName));
  connect(_sourceModel, &UniSqlTableModel::error, this, &TableBrowserWindow::onError);
  _sourceModel->setTable(_tableName);
  _sourceModel->select();
  _proxyModel = new QSortFilterProxyModel(this);
  _proxyModel->setSourceModel(_sourceModel);
  ui->tableView->setModel(_proxyModel);
  ui->tableView->setItemDelegate(new TableBrowserDelegate(_tableItem, this));

  _mnuContext = new QMenu(this);
  _mnuContext->addAction(ui->aSetNull);
  _mnuContext->addAction(ui->aLoadFromFile);
  _mnuContext->addSeparator();
  _mnuContext->addAction(ui->aEqualFilter);
  _mnuContext->addAction(ui->aNotEqualFilter);
  _mnuContext->addAction(ui->aGreaterThanFilter);
  _mnuContext->addAction(ui->aLessThanFilter);
  _mnuContext->addAction(ui->aFilterIsNull);
  _mnuContext->addAction(ui->aFilterIsNotNull);

  _mnuFilterList = new QMenu(this);
  _mnuFilterList->addAction(ui->aRemoveFilter);

  qDebug() << "TableBrowserWindow" << objectName() << "created";

  ui->tableView->horizontalHeader()->setSectionsMovable(true);

  ui->lvFilters->setModel(_sourceModel->filter());

  connect(ui->tableView->selectionModel(), &QItemSelectionModel::currentChanged,
          this, &TableBrowserWindow::onCurrentItemChanged);

  int dbId = DataStore::databaseIdFromItem(_tableItem);
  QByteArray tableStateData = DataStore::loadTableState(dbId, _tableName);
  if (!tableStateData.isEmpty())
    ui->tableView->horizontalHeader()->restoreState(tableStateData);
}

TableBrowserWindow::~TableBrowserWindow()
{
  int dbId = DataStore::databaseIdFromItem(_tableItem);
  DataStore::saveTableState(dbId, _tableName, ui->tableView->horizontalHeader()->saveState());
  qDebug() << "TableBrowserWindow" << objectName() << "destroyed";
  delete ui;
}

void TableBrowserWindow::on_aSubmit_triggered()
{
  bool resOk = _sourceModel->submitAll();
  if (!resOk) {
    QMessageBox::warning(this, TITLE_ERROR, _sourceModel->sqlError().join("\n"));
  }
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
  if (ui->tableView->selectionModel()->selection().isEmpty())
    return;

  int curCol = ui->tableView->currentIndex().column();
  QString field = _sourceModel->fieldName(curCol);

  QVariantList values;
  foreach (QModelIndex idx, ui->tableView->selectionModel()->selectedIndexes()) {
    if (idx.column() != curCol)
      continue;
    values.append(idx.data());
  }
  _sourceModel->filter()->addEqualFilter(field, values, false, WhereJoint::And);
  _sourceModel->select();
}

void TableBrowserWindow::on_aNotEqualFilter_triggered()
{
  if (ui->tableView->selectionModel()->selection().isEmpty())
    return;

  int curCol = ui->tableView->currentIndex().column();
  QString field = _sourceModel->fieldName(curCol);

  QVariantList values;
  foreach (QModelIndex idx, ui->tableView->selectionModel()->selectedIndexes()) {
    if (idx.column() != curCol)
      continue;
    values.append(idx.data());
  }
  _sourceModel->filter()->addEqualFilter(field, values, true, WhereJoint::And);
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

void TableBrowserWindow::on_aRemoveFilter_triggered()
{
  int row = ui->lvFilters->currentIndex().row();
  _sourceModel->filter()->removeFilter(row);
  _sourceModel->select();
}

void TableBrowserWindow::on_lvFilters_pressed(const QModelIndex &index)
{
  Q_UNUSED(index)
  if (QApplication::mouseButtons().testFlag(Qt::RightButton)) {
    _mnuFilterList->popup(QCursor::pos());
  }
}

void TableBrowserWindow::onCurrentItemChanged(const QModelIndex &index)
{
  ui->itemViewer->setValue(index.data());
}

void TableBrowserWindow::on_aLoadFromFile_triggered()
{
  QString filepath = QFileDialog::getOpenFileName(this, tr("Open file"));
  if (filepath.isEmpty())
    return;
  QByteArray data = QFileUtils::loadFile(filepath);
  _proxyModel->setData(ui->tableView->currentIndex(), data);
}
