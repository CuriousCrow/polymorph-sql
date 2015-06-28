#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectioneditdialog.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlField>
#include <QMessageBox>
#include <QUrl>
#include "tablebrowserwindow.h"
#include "qdbdatabaseitem.h"
#include "qdbtableitem.h"
#include "qdbobjectitem.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  qDebug() << QSqlDatabase::drivers();
  //Connection to properies DB
  appDB = QSqlDatabase::addDatabase("QSQLITE");
  appDB.setDatabaseName("properties.sqlite");

  qDebug() << appDB.driver()->hasFeature(QSqlDriver::LastInsertId);

  //Trying to connect
  if (!appDB.open()){
    QMessageBox::critical(this, "Error", appDB.lastError().text());
    return;
  }
  qDebug() << "Success!";

  _structureModel = new QStructureItemModel(this, appDB);
  //Showing first column only
  //TODO: create utility methods for hiding columns
  ui->tvDatabaseStructure->setModel(_structureModel);
  for (int i=1; i<_structureModel->columnCount(QModelIndex()); i++){
    ui->tvDatabaseStructure->hideColumn(i);
  }

  _structureContextMenu = new QMenu(ui->tvDatabaseStructure);
  _structureContextMenu->addAction("Edit object", this, SLOT(showEditorForCurrentItem()));
  _structureContextMenu->addAction("Drop object", this, SLOT(dropCurrentDatabaseObject()));

  //Создаем окно редактирования соединений с БД
  _connectionEditDialog = new ConnectionEditDialog(this);
  _connectionEditDialog->setModel(_structureModel);

  //View editor window
  _viewEditorWindow = new ViewEditDialog(this);
  _viewEditorWindow->setModel(_structureModel);

  //Создаем вкладку с редактором SQL-запросов
  _queryEditorWindow = new QueryEditorWindow(this);
  _queryEditorWindow->setStructureModel(_structureModel);
  ui->tabWidget->addTab(_queryEditorWindow, "Sql editor");

  //Удаление вкладки с таблицей
  connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)),
          this, SLOT(removeTabByIndex(int)));
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_aAddDatabase_triggered()
{
  QDBDatabaseItem* newItem = new QDBDatabaseItem("New database");
  if (newItem->insertMe()){
    _structureModel->appendItem(newItem);
    _connectionEditDialog->mapper()->toLast();
    _connectionEditDialog->show();
  }
}

void MainWindow::on_aEditDatabase_triggered()
{
  _connectionEditDialog->show();
}

void MainWindow::on_tvDatabaseStructure_doubleClicked(const QModelIndex &index)
{
  if (!index.isValid())
    return;
  QDBObjectItem* objectItem = itemByIndex(index);
  switch (objectItem->type()) {
  case QDBObjectItem::Database: {
    QDBDatabaseItem* dbItem = (QDBDatabaseItem*)objectItem;
    //Database connection (loading database items)
    if (dbItem->children().isEmpty()){
      if (!dbItem->createDbConnection())
        break;
      dbItem->loadChildren();
      ui->tvDatabaseStructure->expand(index);
    }
    //Database disconnection (clear all database items)
    else {
      _structureModel->deleteChildren(index);
      removeTabsByItemUrl(dbItem->objectUrl().url());
      QSqlDatabase::removeDatabase(dbItem->connectionName());
    }
    _queryEditorWindow->refreshConnectionList();
    break;
  }
  case QDBObjectItem::Table:
  case QDBObjectItem::View:
    //Создаем вкладку с таблицей
    QDBTableItem* tableItem = (QDBTableItem*)objectItem;
    QString itemUrl = tableItem->objectUrl().url();
    QWidget* tableWidget = ui->tabWidget->findChild<QWidget*>(itemUrl);
    if (!tableWidget){
      tableWidget = new TableBrowserWindow(this, tableItem), tableItem->caption();
      ui->tabWidget->addTab(tableWidget, tableItem->caption());
    }
    ui->tabWidget->setCurrentWidget(tableWidget);
    break;
  }
}

void MainWindow::on_tvDatabaseStructure_clicked(const QModelIndex &index)
{
  _connectionEditDialog->onDatabaseIndexChanged(index);
}

void MainWindow::removeTabByIndex(int index)
{
  QWidget* tabWidget = ui->tabWidget->widget(index);
  ui->tabWidget->removeTab(index);
  delete tabWidget;
}

void MainWindow::removeTabsByItemUrl(QString url)
{
  qDebug() << "removing tabs by url" << url;
  int tabCount = ui->tabWidget->count();
  for (int i=tabCount-1; i>=0; i--){
    if (ui->tabWidget->widget(i)->objectName().startsWith(url, Qt::CaseInsensitive))
      removeTabByIndex(i);
  }
}


void MainWindow::on_aRemoveDatabase_triggered()
{
  //TODO: Here should be existance check
  QDBObjectItem* itemToRemove = itemByIndex(ui->tvDatabaseStructure->currentIndex());
  if (itemToRemove->type() == QDBObjectItem::Database){
    removeTabsByItemUrl(itemToRemove->objectUrl().url());
    if (itemToRemove->deleteMe())
      _structureModel->removeRow(ui->tvDatabaseStructure->currentIndex().row(),
                            QModelIndex());
  }
}

void MainWindow::on_tvDatabaseStructure_pressed(const QModelIndex &index)
{
  //Show context menu by right mouse click
  if (QApplication::mouseButtons().testFlag(Qt::RightButton)){
    if (itemByIndex(index)->type() == QDBObjectItem::View){
      _structureContextMenu->popup(QCursor::pos());
    }
  }
}

void MainWindow::showEditorForCurrentItem()
{
  //Show view editor window
  if (itemByIndex(ui->tvDatabaseStructure->currentIndex())->type() == QDBObjectItem::View){
    _viewEditorWindow->onModelIndexChanged(ui->tvDatabaseStructure->currentIndex());
    _viewEditorWindow->show();
  }
  //TODO: Implementation for other DB objects
}

void MainWindow::dropCurrentDatabaseObject()
{
  //Drop database object
  QDBObjectItem* itemToRemove = itemByIndex(ui->tvDatabaseStructure->currentIndex());
  if (itemToRemove->type() == QDBObjectItem::View){
    removeTabsByItemUrl(itemToRemove->objectUrl().url());
    if (itemToRemove->deleteMe())
      _structureModel->removeRow(ui->tvDatabaseStructure->currentIndex().row(),
                            ui->tvDatabaseStructure->currentIndex().parent());
  }
  //TODO: Implementation for other DB objects
}

QDBObjectItem *MainWindow::itemByIndex(QModelIndex index)
{
  return qobject_cast<QDBObjectItem*>(_structureModel->itemByIndex(index));
}
