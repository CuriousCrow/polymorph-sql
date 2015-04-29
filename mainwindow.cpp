#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectioneditdialog.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlField>
#include <QMessageBox>
#include "tablebrowserwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  qDebug() << QSqlDatabase::drivers();
  //Connection to properies DB
  appDB = QSqlDatabase::addDatabase("QSQLITE");
  appDB.setDatabaseName("properties.sqlite");

  //Trying to connect
  if (!appDB.open()){
    QMessageBox::critical(this, "Error", appDB.lastError().text());
    return;
  }
  qDebug() << "Success!";

  mDbStructure = new QDBStructureModel(this, appDB);
  mDbStructure->setTable("STRUCTURE");

  ui->tvDatabaseStructure->setModel(mDbStructure);
  int nameFieldIdx = mDbStructure->fieldIndex("NAME");
  int fieldCount = mDbStructure->columnCount(QModelIndex());
  ui->tvDatabaseStructure->setTreePosition(nameFieldIdx);
  for(int i=0; i<fieldCount; i++){
    if (i != nameFieldIdx)
      ui->tvDatabaseStructure->hideColumn(i);
  }


  mDatabases = new QSqlTableModel(this, appDB);
  mDatabases->setTable("T_DATABASE");
  mDatabases->select();

  initDatabaseItems();

  connectionEditDialog = new ConnectionEditDialog(this);
  connectionEditDialog->setModel(mDatabases);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_aAddDatabase_triggered()
{
  connectionEditDialog->show();
}

void MainWindow::on_aEditDatabase_triggered()
{
//  connectionEditDialog->onDatabaseIndexChanged(ui->lvDatabases->currentIndex());
  connectionEditDialog->show();
}

void MainWindow::initDatabaseItems()
{
  for(int i=0; i<mDatabases->rowCount(); i++){
    qlonglong id = tableData(mDatabases, i, "ID").toLongLong();
    QString name = tableData(mDatabases, i, "NAME").toString();
    mDbStructure->addItem(id, name, 0);
  }
}

void MainWindow::loadDatabaseItems(qlonglong dbId)
{
  QSqlDatabase db = databasePool[dbId];
  QStringList sl = db.tables();
  int tableIdx = 0;
  foreach (QString table, sl) {
    tableIdx++;
    qlonglong tableId = 100*dbId+tableIdx;
    mDbStructure->addItem(tableId, table, 1, dbId);
    QSqlRecord tableRec = db.record(table);
    for(int fidx = 0; fidx < tableRec.count(); fidx++){
      qlonglong fieldId = 100*tableId + fidx;
      mDbStructure->addItem(fieldId, tableRec.fieldName(fidx), 2, tableId);
    }
  }
}

QVariant MainWindow::tableData(QSqlTableModel *model, int row, QString field)
{
  return model->data(model->index(row, model->fieldIndex(field)));
}

int MainWindow::databaseRowById(qlonglong id)
{
  for(int i=0; i<mDatabases->rowCount(); i++){
    qlonglong curId = tableData(mDatabases, i, "ID").toLongLong();
    if (curId == id)
      return i;
  }
  return -1;
}

void MainWindow::on_tvDatabaseStructure_doubleClicked(const QModelIndex &index)
{
  if (!index.isValid())
    return;
  int itemType = mDbStructure->recById(index.internalId()).value("TYPE").toInt();
  if (itemType == 0){
    //Загружаем структуру БД
    int dbRow = databaseRowById(index.internalId());
    QSqlDatabase newDb = QSqlDatabase::addDatabase("QSQLITE");
    newDb.setDatabaseName(tableData(mDatabases, dbRow, "LOCAL_PATH").toString());
    //Проверка соединения с БД
    if (!newDb.open()){
      qDebug() << newDb.lastError().text();
      return;
    }
    qDebug() << "Success!";
    databasePool.insert(index.internalId(), newDb);
    loadDatabaseItems(index.internalId());
  }
  else if (itemType == 1){
    //Создаем вкладку с таблицей
    qlonglong dbID = index.parent().internalId();
    QString tableName = index.data().toString();
    TableBrowserWindow* tableWindow =
        new TableBrowserWindow(this, databasePool.value(dbID), tableName);
    ui->tabWidget->addTab(tableWindow, tableName);
  }
}
