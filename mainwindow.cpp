#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlField>
#include <QMessageBox>
#include "dbms/appurl.h"
#include "tablebrowserwindow.h"
#include "dbms/dbdatabaseitem.h"
#include "dbms/dbobjectitem.h"
#include "dbms/foldertreeitem.h"
#include "qknowledgebase.h"
#include "core/appsettings.h"
#include "core/datastore.h"
#include "core/core.h"
#include "dbms/appconst.h"
#include "dbms/POSTGRES/postgresplugin.h"
#include "dbms/SQLITE/sqliteplugin.h"
#include "dbms/FIREBIRD/firebirdplugin.h"
#include "dbms/MYSQL/mysqlplugin.h"

MainWindow::MainWindow(QWidget *parent) :
  NotifiableWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  //Loading DBMS plugins
  Core::instance(this);
  Core::registerModule(new PostgresPlugin());
  Core::registerModule(new SqlitePlugin());
  Core::registerModule(new FirebirdPlugin());
  Core::registerModule(new MysqlPlugin());

  //
  DataStore* ds = DataStore::instance(this);
  QStructureItemModel* structureModel = ds->structureModel();

  QStringList modules = Core::instance()->moduleNames();
  QKnowledgeBase::kb(this)->loadModels(modules);

  //Showing first column only
  //TODO: create utility methods for hiding columns
  ui->tvDatabaseStructure->setModel(structureModel);
  for (int i=1; i<structureModel->columnCount(QModelIndex()); i++){
    ui->tvDatabaseStructure->hideColumn(i);
  }

  _itemContextMenu = new QMenu(ui->tvDatabaseStructure);
  connect(_itemContextMenu, SIGNAL(aboutToShow()),
          this, SLOT(updateStructureContextMenu()));
  _editAction = _itemContextMenu->addAction("Edit object", this, SLOT(showEditorForCurrentItem()));
  _dropAction = _itemContextMenu->addAction("Drop object", this, SLOT(dropCurrentDatabaseObject()));
  _exportAction = _itemContextMenu->addAction("Export DDL", this, SLOT(exportCurrrentDatabaseObject()));

  _folderContextMenu = new QMenu(ui->tvDatabaseStructure);
  _folderContextMenu->addAction("Create object", this, SLOT(showCreateItemEditor()));
  _reloadAction = _folderContextMenu->addAction("Refresh", this, SLOT(reloadItemChildren()));


  //Создаем окно редактирования соединений с БД
  _connectionEditDialog = new ConnectionEditDialog(this);
  connect(_connectionEditDialog, SIGNAL(accepted()),
          this, SLOT(saveDatabaseChanges()));

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
  DBDatabaseItem* newItem = new DBDatabaseItem(DEF_DATABASE_NAME);
  _connectionEditDialog->setUserAction(AbstractDatabaseEditForm::Create);
  _connectionEditDialog->setObjItem(newItem);
  _connectionEditDialog->objectToForm();
  _connectionEditDialog->show();
}

void MainWindow::on_aEditDatabase_triggered()
{
  if (!ui->tvDatabaseStructure->currentIndex().isValid())
    return;
  DBObjectItem* curItem = itemByIndex(ui->tvDatabaseStructure->currentIndex());
  _connectionEditDialog->setUserAction(AbstractDatabaseEditForm::Edit);
  _connectionEditDialog->setObjItem(curItem);
  _connectionEditDialog->objectToForm();
  _connectionEditDialog->show();
}

void MainWindow::on_tvDatabaseStructure_doubleClicked(const QModelIndex &index)
{
  if (!index.isValid())
    return;
  DBObjectItem* objectItem = itemByIndex(index);
  switch (objectItem->type()) {
  case DBObjectItem::Database: {
    DBDatabaseItem* dbItem = qobject_cast<DBDatabaseItem*>(objectItem);
    //Database connection (loading database items)
    if (dbItem->children().isEmpty()){
      if (!dbItem->createDbConnection())
        break;
      DbmsPlugin* dbms = Core::module(dbItem->driverName());
      foreach (DBObjectItem::ItemType type, dbms->supportedTypes()) {
        FolderTreeItem* folder = new FolderTreeItem(typeName(type), dbms->folderName(type), dbItem);
        folder->setParentUrl(dbItem->objectUrl());
        folder->setChildrenType(type);
        dbms->loadFolder(folder, type);
      }
      ui->tvDatabaseStructure->reset();
      ui->tvDatabaseStructure->expand(index);
    }
    //Database disconnection (clear all database items)
    else {
      DataStore::structureModel()->deleteChildren(index);
      removeTabsByItemUrl(dbItem->objectUrl().toString());
      QSqlDatabase::removeDatabase(dbItem->connectionName());
    }
    refreshConnectionList();

    break;
  }
  case DBObjectItem::Folder:
    ui->tvDatabaseStructure->setExpanded(index, !ui->tvDatabaseStructure->isExpanded(index));
    break;
  case DBObjectItem::Table:
  case DBObjectItem::View: {
    //Show or add table editor
    DBTableItem* tableItem = qobject_cast<DBTableItem*>(objectItem);
    openTableEditor(tableItem);
    break;
  }
  case DBObjectItem::Sequence:
  case DBObjectItem::Procedure:
  case DBObjectItem::Trigger:
    showEditorForCurrentItem();
    break;
  }
}

void MainWindow::on_tvDatabaseStructure_clicked(const QModelIndex &index)
{
  DBObjectItem* curItem = qobject_cast<DBObjectItem*>(DataStore::structureModel()->itemByIndex(index));
  qDebug() << "Obj url:" << curItem->objectName();

  ui->aEditDatabase->setEnabled(curItem->type() == DBObjectItem::Database);
  ui->aRemoveDatabase->setEnabled(curItem->type() == DBObjectItem::Database);
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
  DBObjectItem* itemToRemove = itemByIndex(ui->tvDatabaseStructure->currentIndex());
  if (itemToRemove->type() == DBObjectItem::Database){
    removeTabsByItemUrl(itemToRemove->objectUrl().toString());
    ActionResult res = itemToRemove->deleteMe();
    if (res.isSuccess()) {
      DataStore::instance()->structureModel()->removeRow(ui->tvDatabaseStructure->currentIndex().row(), QModelIndex());
    }
    else {
      qWarning() << "Remove database error:" << res.description();
    }
  }
}

void MainWindow::on_tvDatabaseStructure_pressed(const QModelIndex &index)
{
  //Show context menu by right mouse click
  if (QApplication::mouseButtons().testFlag(Qt::RightButton)){
    switch (itemByIndex(index)->type()) {
    case DBObjectItem::View:
    case DBObjectItem::Trigger:
    case DBObjectItem::Table:
      _itemContextMenu->popup(QCursor::pos());
      break;
    case DBObjectItem::Folder:
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
  DBObjectItem* currentItem = itemByIndex(ui->tvDatabaseStructure->currentIndex());
  switch (currentItem->type()) {
  case DBObjectItem::View:
    currentItem->refresh();
    _viewEditorWindow->setObjItem(currentItem);
    _viewEditorWindow->setUserAction(AbstractDatabaseEditForm::Edit);
    _viewEditorWindow->objectToForm();
    _viewEditorWindow->show();
    break;
  case DBObjectItem::Table:
    _tableEditForm->setUserAction(AbstractDatabaseEditForm::Edit);
    _tableEditForm->setObjItem(currentItem);
    _tableEditForm->objectToForm();
    _tableEditForm->show();
    break;
  case DBObjectItem::Sequence:
    currentItem->refresh();
    _sequenceEditForm->setUserAction(AbstractDatabaseEditForm::Edit);
    _sequenceEditForm->setObjItem(currentItem);
    _sequenceEditForm->objectToForm();
    _sequenceEditForm->show();
    break;
  case DBObjectItem::Procedure:
    currentItem->refresh();
    _procedureEditForm->setUserAction(AbstractDatabaseEditForm::Edit);
    _procedureEditForm->setObjItem(currentItem);
    _procedureEditForm->objectToForm();
    _procedureEditForm->show();
    break;
  case DBObjectItem::Trigger:
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
  DBObjectItem* itemToRemove = itemByIndex(ui->tvDatabaseStructure->currentIndex());
  switch (itemToRemove->type()) {
  case DBObjectItem::View:
  case DBObjectItem::Table:
  case DBObjectItem::Trigger:
  case DBObjectItem::Sequence:
  case DBObjectItem::Procedure: {
    removeTabsByItemUrl(itemToRemove->objectUrl().toString());
    ActionResult res = itemToRemove->deleteMe();
    if (res.isSuccess()) {
      DataStore::structureModel()->removeRow(ui->tvDatabaseStructure->currentIndex().row(),
                                 ui->tvDatabaseStructure->currentIndex().parent());
      refreshQueryEditorAssistance();
    }
    else {
      QMessageBox::warning(this, TITLE_ERROR, "Delete operation failed: " + res.description());
    }
    break;
  }
  default:
    break;
  }
  //TODO: Implementation for other DB objects
}

void MainWindow::exportCurrrentDatabaseObject()
{
  //TODO: Test implementation
  QModelIndex curIdx = ui->tvDatabaseStructure->currentIndex();
  DBObjectItem* curObj = itemByIndex(curIdx);
  curObj->refresh();
  qDebug() << "DDL:" << curObj->toDDL();
}

void MainWindow::reloadItemChildren()
{
  QModelIndex curIdx = ui->tvDatabaseStructure->currentIndex();
  DataStore::structureModel()->deleteChildren(curIdx);
  FolderTreeItem* folderItem = qobject_cast<FolderTreeItem*>(itemByIndex(curIdx));

  qDebug() << "Folder" << folderItem->fieldValue(F_CAPTION).toString() << "refresh request";

  DbmsPlugin* dbms = Core::module(folderItem->driverName());
  dbms->loadFolder(folderItem, folderItem->childrenType());

  DataStore::structureModel()->dataChanged(curIdx, curIdx);
}

void MainWindow::updateStructureContextMenu()
{
  DBObjectItem* item = itemByIndex(ui->tvDatabaseStructure->currentIndex());
  _editAction->setText(item->isEditable() ? tr("Edit object") : tr("View object"));
}

void MainWindow::showCreateItemEditor()
{
  qDebug() << "Create window";
  DBObjectItem* currentItem = itemByIndex(ui->tvDatabaseStructure->currentIndex());

  if (currentItem->type() != DBObjectItem::Folder) {
    qWarning() << "Create item action: Not folder item";
    return;
  }
  FolderTreeItem* folderItem = qobject_cast<FolderTreeItem*>(currentItem);
  DbmsPlugin* dbms = Core::module(folderItem->driverName());

  switch (folderItem->childrenType()) {
  case DBObjectItem::Table: {
    DBTableItem* newTableItem = dbms->newTableItem(DEF_TABLE_NAME);
    newTableItem->setParentUrl(folderItem->objectUrl());
    _tableEditForm->setObjItem(newTableItem);
    _tableEditForm->setUserAction(AbstractDatabaseEditForm::Create);
    _tableEditForm->objectToForm();
    _tableEditForm->show();
    break;
  }
  case DBObjectItem::View: {
    DBTableItem* newViewItem = dbms->newViewItem(DEF_VIEW_NAME);
    newViewItem->setParentUrl(folderItem->objectUrl());
    _viewEditorWindow->setObjItem(newViewItem);
    _viewEditorWindow->setUserAction(AbstractDatabaseEditForm::Create);
    _viewEditorWindow->objectToForm();
    _viewEditorWindow->show();
    break;
  }
  case DBObjectItem::Sequence: {
    DBSequenceItem* newSequenceItem = dbms->newSequenceItem(DEF_SEQUENCE_NAME);
    newSequenceItem->setParentUrl(folderItem->objectUrl());
    _sequenceEditForm->setObjItem(newSequenceItem);
    _sequenceEditForm->setUserAction(AbstractDatabaseEditForm::Create);
    _sequenceEditForm->objectToForm();
    _sequenceEditForm->show();
    break;
  }
  case DBObjectItem::Procedure: {
    DBProcedureItem* newProcedureItem = dbms->newProcedureItem(DEF_PROCEDURE_NAME);
    newProcedureItem->setParentUrl(folderItem->objectUrl());
    _procedureEditForm->setObjItem(newProcedureItem);
    _procedureEditForm->setUserAction(AbstractDatabaseEditForm::Create);
    _procedureEditForm->objectToForm();
    _procedureEditForm->show();
    break;
  }
  case DBObjectItem::Trigger: {
    DBTriggerItem* newTriggerItem = dbms->newTriggerItem(DEF_TRIGGER_NAME);
    newTriggerItem->setParentUrl(folderItem->objectUrl());
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

void MainWindow::saveDatabaseChanges()
{
  AbstractDatabaseEditForm* editForm = qobject_cast<AbstractDatabaseEditForm*>(sender());
  AbstractDatabaseEditForm::UserAction action = editForm->userAction();
  if (action == AbstractDatabaseEditForm::Create) {
    DBObjectItem* newItem = editForm->objItem();
    DataStore::structureModel()->appendItem(newItem);
    refreshQueryEditorAssistance();
  }
  else {
    qWarning() << "Connection delete action is not possible from edit form";
  }
}

void MainWindow::saveTableChanges()
{
  AbstractDatabaseEditForm* editForm = qobject_cast<AbstractDatabaseEditForm*>(sender());
  AbstractDatabaseEditForm::UserAction action = editForm->userAction();
  if (action == AbstractDatabaseEditForm::Create) {
    DBObjectItem* folderItem = itemByIndex(ui->tvDatabaseStructure->currentIndex());
    DBObjectItem* newItem = editForm->objItem();
    DataStore::structureModel()->appendItem(newItem, folderItem);
    refreshQueryEditorAssistance();
  }
  else if (action == AbstractDatabaseEditForm::Edit) {
    refreshQueryEditorAssistance();
  }
  else {
    qWarning() << "Table delete action is not possible from edit form";
  }
}

void MainWindow::saveViewChanges()
{
  AbstractDatabaseEditForm* editForm = qobject_cast<AbstractDatabaseEditForm*>(sender());
  AbstractDatabaseEditForm::UserAction action = editForm->userAction();
  if (action == AbstractDatabaseEditForm::Create) {
    DBObjectItem* folderItem = itemByIndex(ui->tvDatabaseStructure->currentIndex());
    DBObjectItem* newItem = editForm->objItem();
    DataStore::structureModel()->appendItem(newItem, folderItem);
    refreshQueryEditorAssistance();
  }
  else {
    qWarning() << "Table delete action is not possible from edit form";
  }
}

void MainWindow::saveSequenceChanges()
{
  AbstractDatabaseEditForm* editForm = qobject_cast<AbstractDatabaseEditForm*>(sender());
  AbstractDatabaseEditForm::UserAction action = editForm->userAction();
  if (action == AbstractDatabaseEditForm::Create) {
    DBObjectItem* folderItem = itemByIndex(ui->tvDatabaseStructure->currentIndex());
    DBObjectItem* newItem = editForm->objItem();
    DataStore::structureModel()->appendItem(newItem, folderItem);
    refreshQueryEditorAssistance();
  }
  else if (action == AbstractDatabaseEditForm::Edit) {
    refreshQueryEditorAssistance();
  }
}

void MainWindow::saveProcedureChanges()
{
  AbstractDatabaseEditForm* editForm = qobject_cast<AbstractDatabaseEditForm*>(sender());
  AbstractDatabaseEditForm::UserAction action = editForm->userAction();
  if (action == AbstractDatabaseEditForm::Create) {
    DBObjectItem* folderItem = itemByIndex(ui->tvDatabaseStructure->currentIndex());
    DBObjectItem* newItem = editForm->objItem();
    DataStore::structureModel()->appendItem(newItem, folderItem);
    refreshQueryEditorAssistance();
  }
  else if (action == AbstractDatabaseEditForm::Edit) {
    refreshQueryEditorAssistance();
  }
}

void MainWindow::saveTriggerChanges()
{
  AbstractDatabaseEditForm* editForm = qobject_cast<AbstractDatabaseEditForm*>(sender());
  AbstractDatabaseEditForm::UserAction action = editForm->userAction();
  if (action == AbstractDatabaseEditForm::Create) {
    DBObjectItem* folderItem = itemByIndex(ui->tvDatabaseStructure->currentIndex());
    DBObjectItem* newItem = editForm->objItem();
    DataStore::structureModel()->appendItem(newItem, folderItem);
    refreshQueryEditorAssistance();
  }
  else if (action == AbstractDatabaseEditForm::Edit) {
    refreshQueryEditorAssistance();
  }
}

DBObjectItem *MainWindow::itemByIndex(QModelIndex index)
{
  return qobject_cast<DBObjectItem*>(DataStore::structureModel()->itemByIndex(index));
}

DBObjectItem *MainWindow::itemByName(QString name)
{
  return qobject_cast<DBObjectItem*>(DataStore::structureModel()->itemByName(name));
}

QString MainWindow::typeName(DBObjectItem::ItemType type)
{
  switch (type) {
  case DBObjectItem::Table:
    return FOLDER_TABLES;
  case DBObjectItem::SystemTable:
    return FOLDER_SYSTABLES;
  case DBObjectItem::View:
    return FOLDER_VIEWS;
  case DBObjectItem::Trigger:
    return FOLDER_TRIGGERS;
  case DBObjectItem::Sequence:
    return FOLDER_SEQUENCES;
  case DBObjectItem::Procedure:
    return FOLDER_PROCEDURES;
  default:
    return "unknown";
  }
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
      editor->reloadKnowledgeModel();
  }
}

void MainWindow::showItemInfoWidget(DBObjectItem *dbItem)
{
  switch (dbItem->type()) {
  case DBObjectItem::Table:
  case DBObjectItem::View:
    //Show or add table editor
    DBTableItem* tableItem = qobject_cast<DBTableItem*>(dbItem);
    openTableEditor(tableItem);
    break;
  }
}

void MainWindow::openTableEditor(DBTableItem *tableItem)
{
  QString itemUrl = tableItem->objectUrl().toString();
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
    DBObjectItem* item = itemByName(event->url());
    if (item)
      showItemInfoWidget(item);
  }
}

void MainWindow::on_aOpenSqlEditor_triggered()
{
  //Создаем вкладку с редактором SQL-запросов
  QueryEditorWindow* newQueryEditor = new QueryEditorWindow(this);
  ui->tabWidget->addTab(newQueryEditor, tr("Query"));
}
