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
#include "qfoldertreeitem.h"
#include "qdbsqlitetableitem.h"
#include "qdbmysqltableitem.h"
#include "qknowledgebase.h"
#include "core/appsettings.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);  

  qDebug() << QSqlDatabase::drivers();
  //Connection to properies DB
  appDB = QSqlDatabase::addDatabase("QSQLITE");
  QString dbPath = AppSettings::strVal("database", "properties.sqlite");
  qDebug() << "dbPath:" << dbPath;
  appDB.setDatabaseName(dbPath);

  qDebug() << appDB.driver()->hasFeature(QSqlDriver::LastInsertId);

  //Trying to connect
  if (!appDB.open()){
    QMessageBox::critical(this, "Error", appDB.lastError().text());
    return;
  }
  qDebug() << "Success!";

  QKnowledgeBase::kb(this);

  _structureModel = new QStructureItemModel(this, appDB);
  //Showing first column only
  //TODO: create utility methods for hiding columns
  ui->tvDatabaseStructure->setModel(_structureModel);
  for (int i=1; i<_structureModel->columnCount(QModelIndex()); i++){
    ui->tvDatabaseStructure->hideColumn(i);
  }

  _itemContextMenu = new QMenu(ui->tvDatabaseStructure);
  connect(_itemContextMenu, SIGNAL(aboutToShow()),
          this, SLOT(updateStructureContextMenu()));
  _editAction = _itemContextMenu->addAction("Edit object", this, SLOT(showEditorForCurrentItem()));
  _dropAction = _itemContextMenu->addAction("Drop object", this, SLOT(dropCurrentDatabaseObject()));

  _folderContextMenu = new QMenu(ui->tvDatabaseStructure);
  _folderContextMenu->addAction("Create object", this, SLOT(showCreateItemEditor()));


  //Создаем окно редактирования соединений с БД
  _connectionEditDialog = new ConnectionEditDialog(this);
  _connectionEditDialog->setModel(_structureModel);

  //View editor window
  _viewEditorWindow = new ViewEditDialog(this);
  _viewEditorWindow->setModel(_structureModel);

  //Table item editor
  _tableEditForm = new TableEditForm(this);
  _tableEditForm->setModal(true);
  connect(_tableEditForm, SIGNAL(accepted()),
          this, SLOT(saveTableChanges()));

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
      ui->tvDatabaseStructure->reset();
      ui->tvDatabaseStructure->expand(index);
    }
    //Database disconnection (clear all database items)
    else {
      _structureModel->deleteChildren(index);
      removeTabsByItemUrl(dbItem->objectUrl().url());
      QSqlDatabase::removeDatabase(dbItem->connectionName());
    }
    //Update combobox model in SQL editor
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
      tableWidget = new TableBrowserWindow(this, tableItem);
      ui->tabWidget->addTab(tableWidget, tableItem->fieldValue("caption").toString());
    }
    ui->tabWidget->setCurrentWidget(tableWidget);
    QSqlQueryHelper::tableRowInfo(tableItem->fieldValue("caption").toString(), tableItem->connectionName());
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
    switch (itemByIndex(index)->type()) {
    case QDBObjectItem::View:
    case QDBObjectItem::Trigger:
    case QDBObjectItem::Table:
      _itemContextMenu->popup(QCursor::pos());
      break;
    case QDBObjectItem::Folder:
      _folderContextMenu->popup(QCursor::pos());
      break;
    default:
      _itemContextMenu->popup(QCursor::pos());
      break;
    }
  }
}

void MainWindow::showEditorForCurrentItem()
{
  //Show view editor window
  QDBObjectItem* currentItem = itemByIndex(ui->tvDatabaseStructure->currentIndex());
  switch (currentItem->type()) {
  case QDBObjectItem::View:
    _viewEditorWindow->onModelIndexChanged(ui->tvDatabaseStructure->currentIndex());
    _viewEditorWindow->show();
    break;
  case QDBObjectItem::Table:
    _tableEditForm->setUserAction(AbstractDatabaseEditForm::Edit);
    _tableEditForm->setObjItem(currentItem);
    _tableEditForm->objectToForm();
    _tableEditForm->show();
    break;
  default:
    QMessageBox::warning(this, "Warning", "Edit form isn't supported yet");
  }
  //TODO: Implementation for other DB objects
}

void MainWindow::dropCurrentDatabaseObject()
{
  //Drop database object
  QDBObjectItem* itemToRemove = itemByIndex(ui->tvDatabaseStructure->currentIndex());
  switch (itemToRemove->type()) {
  case QDBObjectItem::View:
  case QDBObjectItem::Table:
  case QDBObjectItem::Trigger:
      removeTabsByItemUrl(itemToRemove->objectUrl().url());
      if (itemToRemove->deleteMe())
        _structureModel->removeRow(ui->tvDatabaseStructure->currentIndex().row(),
                              ui->tvDatabaseStructure->currentIndex().parent());
      break;
  default:
      break;
  }
  //TODO: Implementation for other DB objects
}

void MainWindow::updateStructureContextMenu()
{
    QDBObjectItem* item = itemByIndex(ui->tvDatabaseStructure->currentIndex());
    _editAction->setText(item->isEditable() ? tr("Edit object") : tr("View object"));
}

void MainWindow::showCreateItemEditor()
{
  qDebug() << "Create window";
  QDBObjectItem* currentItem = itemByIndex(ui->tvDatabaseStructure->currentIndex());
  QFolderTreeItem* folderItem = qobject_cast<QFolderTreeItem*>(currentItem);
  QDBDatabaseItem* databaseItem = qobject_cast<QDBDatabaseItem*>(folderItem->parent());
  if (!folderItem) {
    qWarning() << "Create item action: Not folder item";
    return;
  }
  QDBTableItem* newTableItem;
  switch (folderItem->childrenType()) {
  case QDBObjectItem::Table: {
    //Здесь не должно быть СУБД зависимого кода (необходимо перенести фабричный метод в QDBDatabaseItem)
    qDebug() << "Folder item connection:" << databaseItem->connectionName();
    QString driverName = QSqlQueryHelper::driverName(databaseItem->connectionName());
    if (driverName.compare("QSQLITE") == 0) {
      newTableItem = new QDBSqliteTableItem("QDBSqliteTableItem");
    }
    else if (driverName.compare("QMYSQL") == 0) {
      newTableItem = new QDBMysqlTableItem("QDBMysqlTableItem");
    }
    else {
      newTableItem = new QDBTableItem("QDBTableItem");
    }
    _tableEditForm->setObjItem(newTableItem);
    _tableEditForm->setUserAction(AbstractDatabaseEditForm::Create);
    _tableEditForm->objectToForm();
    _tableEditForm->show();
    break;
  }
  default:
    break;
  }
}

void MainWindow::saveTableChanges()
{
  AbstractDatabaseEditForm* editForm = qobject_cast<AbstractDatabaseEditForm*>(sender());
  AbstractDatabaseEditForm::UserAction action = editForm->userAction();
  if (action == AbstractDatabaseEditForm::Drop) {
    editForm->objItem()->deleteMe();
    _queryEditorWindow->refreshCompleterData();
  }
  else if (action == AbstractDatabaseEditForm::Create) {    
    QDBObjectItem* currentItem = itemByIndex(ui->tvDatabaseStructure->currentIndex());
    _structureModel->appendItem(editForm->objItem(), currentItem);
    editForm->objItem()->insertMe();
    _queryEditorWindow->refreshCompleterData();
  }
  else {
    editForm->objItem()->updateMe();
    _queryEditorWindow->refreshCompleterData();
  }
}

QDBObjectItem *MainWindow::itemByIndex(QModelIndex index)
{
  return qobject_cast<QDBObjectItem*>(_structureModel->itemByIndex(index));
}
