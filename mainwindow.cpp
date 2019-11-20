#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectioneditdialog.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlField>
#include <QMessageBox>
#include <QUrl>
#include "tablebrowserwindow.h"
#include "dbms/qdbdatabaseitem.h"
#include "dbms/qdbobjectitem.h"
#include "dbms/qfoldertreeitem.h"
//#include "dbms/SQLITE/qdbsqlitetableitem.h"
//#include "dbms/MYSQL/qdbmysqltableitem.h"
#include "qknowledgebase.h"
#include "core/appsettings.h"
#include "dbms/appconst.h"

MainWindow::MainWindow(QWidget *parent) :
  NotifiableWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  qDebug() << QSqlDatabase::drivers();
  //Connection to properies DB
  appDB = QSqlDatabase::addDatabase(DRIVER_SQLITE);
  QString dbPath = AppSettings::strVal(PRM_DATABASE, "properties.sqlite");
  qDebug() << "dbPath:" << dbPath;
  appDB.setDatabaseName(dbPath);

  qDebug() << appDB.driver()->hasFeature(QSqlDriver::LastInsertId);

  //Trying to connect
  if (!appDB.open()){
    QMessageBox::critical(this, TITLE_ERROR, appDB.lastError().text());
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
  connect(_viewEditorWindow, SIGNAL(accepted()),
          this, SLOT(saveViewChanges()));

  //Table item editor
  _tableEditForm = new TableEditForm(this);
  _tableEditForm->setModal(true);
  connect(_tableEditForm, SIGNAL(accepted()),
          this, SLOT(saveTableChanges()));

  _sequenceEditForm = new SequenceEditForm(this);
  _sequenceEditForm->setModal(true);
  connect(_sequenceEditForm, SIGNAL(accepted()),
          this, SLOT(saveSequenceChanges()));

  _procedureEditForm = new ProcedureEditForm(this);
  connect(_procedureEditForm, SIGNAL(accepted()),
          this, SLOT(saveProcedureChanges()));

  _triggerEditForm = new TriggerEditForm(this);
  connect(_triggerEditForm, SIGNAL(accepted()),
          this, SLOT(saveTriggerChanges()));

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
  QDBDatabaseItem* newItem = new QDBDatabaseItem(DEF_DATABASE_NAME);
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
    QDBDatabaseItem* dbItem = qobject_cast<QDBDatabaseItem*>(objectItem);
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
    refreshConnectionList();

    break;
  }
  case QDBObjectItem::Folder:
    ui->tvDatabaseStructure->setExpanded(index, !ui->tvDatabaseStructure->isExpanded(index));
    break;
  case QDBObjectItem::Table:
  case QDBObjectItem::View: {
    //Show or add table editor
    QDBTableItem* tableItem = qobject_cast<QDBTableItem*>(objectItem);
    openTableEditor(tableItem);
    break;
  }
  case QDBObjectItem::Sequence:
  case QDBObjectItem::Procedure:
  case QDBObjectItem::Trigger:
    showEditorForCurrentItem();
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
      _structureModel->removeRow(ui->tvDatabaseStructure->currentIndex().row(), QModelIndex());
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
    _viewEditorWindow->setObjItem(currentItem);
    _viewEditorWindow->setUserAction(AbstractDatabaseEditForm::Edit);
    _viewEditorWindow->objectToForm();
    _viewEditorWindow->show();
    break;
  case QDBObjectItem::Table:
    _tableEditForm->setUserAction(AbstractDatabaseEditForm::Edit);
    _tableEditForm->setObjItem(currentItem);
    _tableEditForm->objectToForm();
    _tableEditForm->show();
    break;
  case QDBObjectItem::Sequence:
    currentItem->refresh();
    _sequenceEditForm->setUserAction(AbstractDatabaseEditForm::Edit);
    _sequenceEditForm->setObjItem(currentItem);
    _sequenceEditForm->objectToForm();
    _sequenceEditForm->show();
    break;
  case QDBObjectItem::Procedure:
    currentItem->refresh();
    _procedureEditForm->setUserAction(AbstractDatabaseEditForm::Edit);
    _procedureEditForm->setObjItem(currentItem);
    _procedureEditForm->objectToForm();
    _procedureEditForm->show();
    break;
  case QDBObjectItem::Trigger:
    currentItem->refresh();
    _triggerEditForm->setUserAction(AbstractDatabaseEditForm::Edit);
    _triggerEditForm->setObjItem(currentItem);
    _triggerEditForm->objectToForm();
    _triggerEditForm->show();
    break;
  default:
    QMessageBox::warning(this, TITLE_WARNING, "Edit form isn't supported yet");
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
  case QDBObjectItem::Sequence:
  case QDBObjectItem::Procedure:
    removeTabsByItemUrl(itemToRemove->objectUrl().url());
    if (itemToRemove->deleteMe()) {
      _structureModel->removeRow(ui->tvDatabaseStructure->currentIndex().row(),
                                 ui->tvDatabaseStructure->currentIndex().parent());
      refreshQueryEditorAssistance();
    }
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

  switch (folderItem->childrenType()) {
  case QDBObjectItem::Table: {
    QDBTableItem* newTableItem = databaseItem->createNewTableItem(DEF_TABLE_NAME);
    newTableItem->setDriverName(databaseItem->driverName());
    _tableEditForm->setObjItem(newTableItem);
    _tableEditForm->setUserAction(AbstractDatabaseEditForm::Create);
    _tableEditForm->objectToForm();
    _tableEditForm->show();
    break;
  }
  case QDBObjectItem::View: {
    QDBTableItem* newViewItem = databaseItem->createNewViewItem(DEF_VIEW_NAME);
    _viewEditorWindow->setObjItem(newViewItem);
    _viewEditorWindow->setUserAction(AbstractDatabaseEditForm::Create);
    _viewEditorWindow->objectToForm();
    _viewEditorWindow->show();
    break;
  }
  case QDBObjectItem::Sequence: {
    QDBSequenceItem* newSequenceItem = databaseItem->createNewSequenceItem(DEF_SEQUENCE_NAME);
    _sequenceEditForm->setObjItem(newSequenceItem);
    _sequenceEditForm->setUserAction(AbstractDatabaseEditForm::Create);
    _sequenceEditForm->objectToForm();
    _sequenceEditForm->show();
    break;
  }
  case QDBObjectItem::Procedure: {
    QDBProcedureItem* newProcedureItem = databaseItem->createNewProcedureItem(DEF_PROCEDURE_NAME);
    _procedureEditForm->setObjItem(newProcedureItem);
    _procedureEditForm->setUserAction(AbstractDatabaseEditForm::Create);
    _procedureEditForm->objectToForm();
    _procedureEditForm->show();
    break;
  }
  case QDBObjectItem::Trigger: {
    QDBTriggerItem* newTriggerItem = databaseItem->createNewTriggerItem(DEF_TRIGGER_NAME);
    _triggerEditForm->setObjItem(newTriggerItem);
    _triggerEditForm->setUserAction(AbstractDatabaseEditForm::Create);
    _triggerEditForm->objectToForm();
    _triggerEditForm->show();
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
    refreshQueryEditorAssistance();
  }
  else if (action == AbstractDatabaseEditForm::Create) {
    QDBObjectItem* currentItem = itemByIndex(ui->tvDatabaseStructure->currentIndex());
    _structureModel->appendItem(editForm->objItem(), currentItem);
    editForm->objItem()->insertMe();
    refreshQueryEditorAssistance();
  }
  else {
    editForm->objItem()->updateMe();
    refreshQueryEditorAssistance();
  }
}

void MainWindow::saveViewChanges()
{
  AbstractDatabaseEditForm* editForm = qobject_cast<AbstractDatabaseEditForm*>(sender());
  AbstractDatabaseEditForm::UserAction action = editForm->userAction();
  if (action == AbstractDatabaseEditForm::Create) {
    QDBObjectItem* currentItem = itemByIndex(ui->tvDatabaseStructure->currentIndex());
    _structureModel->appendItem(editForm->objItem(), currentItem);
    editForm->objItem()->insertMe();
    refreshQueryEditorAssistance();
  }
}

void MainWindow::saveSequenceChanges()
{
  AbstractDatabaseEditForm* editForm = qobject_cast<AbstractDatabaseEditForm*>(sender());
  AbstractDatabaseEditForm::UserAction action = editForm->userAction();
  if (action == AbstractDatabaseEditForm::Create) {
    QDBObjectItem* currentItem = itemByIndex(ui->tvDatabaseStructure->currentIndex());
    _structureModel->appendItem(editForm->objItem(), currentItem);
    editForm->objItem()->insertMe();
    refreshQueryEditorAssistance();
  }
  else {
    editForm->objItem()->updateMe();
    refreshQueryEditorAssistance();
  }
}

void MainWindow::saveProcedureChanges()
{

}

void MainWindow::saveTriggerChanges()
{

}

QDBObjectItem *MainWindow::itemByIndex(QModelIndex index)
{
  return qobject_cast<QDBObjectItem*>(_structureModel->itemByIndex(index));
}

QDBObjectItem *MainWindow::itemByName(QString name)
{
  return qobject_cast<QDBObjectItem*>(_structureModel->itemByName(name));
}

void MainWindow::refreshConnectionList()
{
  for(int idx=0; idx<ui->tabWidget->count(); idx++) {
    QueryEditorWindow* editor = qobject_cast<QueryEditorWindow*>(ui->tabWidget->widget(idx));
    if (editor)
      editor->refreshConnectionList();
  }
}

void MainWindow::refreshQueryEditorAssistance()
{
  for(int idx=0; idx<ui->tabWidget->count(); idx++) {
    QueryEditorWindow* editor = qobject_cast<QueryEditorWindow*>(ui->tabWidget->widget(idx));
    if (editor)
      editor->refreshCompleterData();
  }
}

void MainWindow::showItemInfoWidget(QDBObjectItem *dbItem)
{
  switch (dbItem->type()) {
  case QDBObjectItem::Table:
  case QDBObjectItem::View:
    //Show or add table editor
    QDBTableItem* tableItem = qobject_cast<QDBTableItem*>(dbItem);
    openTableEditor(tableItem);
    break;
  }
}

void MainWindow::openTableEditor(QDBTableItem *tableItem)
{
  QString itemUrl = tableItem->objectUrl().url();
  QWidget* tableWidget = ui->tabWidget->findChild<QWidget*>(itemUrl);
  if (!tableWidget){
    tableWidget = new TableBrowserWindow(this, tableItem);
    ui->tabWidget->addTab(tableWidget, tableItem->fieldValue(F_CAPTION).toString());
  }
  ui->tabWidget->setCurrentWidget(tableWidget);
  //  QSqlQueryHelper::tableRowInfo(tableItem->fieldValue(F_CAPTION).toString(), tableItem->connectionName());
}

void MainWindow::localEvent(LocalEvent *event)
{
  qDebug() << "Local event received from" << event->url();
  if (event->type() == ShowObjectEvent) {
    QDBObjectItem* item = itemByName(event->url());
    if (item)
      showItemInfoWidget(item);
  }
}

void MainWindow::on_aOpenSqlEditor_triggered()
{
  //Создаем вкладку с редактором SQL-запросов
  QueryEditorWindow* newQueryEditor = new QueryEditorWindow(this);
  newQueryEditor->setStructureModel(_structureModel);
  ui->tabWidget->addTab(newQueryEditor, tr("Query"));
}
