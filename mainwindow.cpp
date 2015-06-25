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

  //Создаем окно редактирования соединений с БД
  _connectionEditDialog = new ConnectionEditDialog(this);
  _connectionEditDialog->setModel(_structureModel);

  //Создаем вкладку с редактором SQL-запросов
  _queryEditorWindow = new QueryEditorWindow(this);
  _queryEditorWindow->setStructureModel(_structureModel);
  ui->tabWidget->addTab(_queryEditorWindow, "Sql editor");

  //Удаление вкладки с таблицей
  connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)),
          this, SLOT(removeTabByIndex(int)));

  connect(_structureModel, SIGNAL(itemAboutToBeRemoved(QString)), this, SLOT(removeTabsByItemUrl(QString)));
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
  QDBObjectItem* objectItem = (QDBObjectItem*)_structureModel->itemByIndex(index);
  //Double click on database item
  if (objectItem->type() == QDBObjectItem::Database){
    QDBDatabaseItem* dbItem = (QDBDatabaseItem*)_structureModel->itemByIndex(index);
    //Database connection (loading database items)
    if (dbItem->children().isEmpty()){
      if (!dbItem->createDbConnection())
        return;
      dbItem->loadChildren();
      ui->tvDatabaseStructure->expand(index);
    }
    //Database disconnection (clear all database items)
    else {
      _structureModel->deleteChildren(index);
      QSqlDatabase::removeDatabase(dbItem->connectionName());
    }
    _queryEditorWindow->refreshConnectionList();
  }
  //Double click on table item
  else if (objectItem->type() == QDBObjectItem::Table){
    //Создаем вкладку с таблицей
    QDBTableItem* tableItem = (QDBTableItem*)_structureModel->itemByIndex(index);
    QString itemUrl = tableItem->objectUrl().url();
    QWidget* tableWidget = ui->tabWidget->findChild<QWidget*>(itemUrl);
    if (!tableWidget){
      tableWidget = new TableBrowserWindow(this, tableItem), tableItem->caption();
      ui->tabWidget->addTab(tableWidget, tableItem->caption());
    }
    ui->tabWidget->setCurrentWidget(tableWidget);
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
  QDBObjectItem* itemToRemove = (QDBObjectItem*)_structureModel->itemByIndex(ui->tvDatabaseStructure->currentIndex());
  if (itemToRemove->type() == QDBObjectItem::Database){
    if (itemToRemove->deleteMe())
      _structureModel->removeRow(ui->tvDatabaseStructure->currentIndex().row(),
                            QModelIndex());
  }
}
