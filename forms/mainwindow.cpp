#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlField>
#include <QMessageBox>
#include <QClipboard>
#include "databaseexportform.h"
#include "sdk/objects/appurl.h"
#include "tablebrowserwindow.h"
#include "settingsform.h"
#include "sdk/objects/dbdatabaseitem.h"
#include "sdk/objects/dbobjectitem.h"
#include "sdk/objects/foldertreeitem.h"
#include "sdk/core/qknowledgebase.h"
#include "sdk/core/appsettings.h"
#include "sdk/core/datastore.h"
#include "sdk/core/core.h"
#include "sdk/objects/appconst.h"
#include "sdk/objects/sdkplugin.h"
#include "plugins/POSTGRES/postgresplugin.h"
#include "plugins/SQLITE/sqliteplugin.h"
#include "plugins/FIREBIRD/firebirdplugin.h"
#include "plugins/MYSQL/mysqlplugin.h"
#include <QPluginLoader>

//#define SINGLEAPP


MainWindow::MainWindow(QWidget *parent) :
  NotifiableWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  //Loading DBMS plugins
  Core::instance(this);
  Core::registerPlugin(new SdkPlugin());

#ifdef SINGLEAPP
  Core::registerPlugin(new PostgresPlugin());
  Core::registerPlugin(new SqlitePlugin());
//  Core::registerPlugin(new FirebirdPlugin());
//  Core::registerPlugin(new MysqlPlugin());
#else
  Core::registerPlugin(new PostgresPlugin());
  QPluginLoader* pluginLoader = new QPluginLoader(this);
  pluginLoader->setFileName("plugins/SqlitePlugin");
  IocPlugin* plugin = qobject_cast<IocPlugin*>(pluginLoader->instance());
  if (plugin) {
      qDebug() << "Plugin is successfully loaded:" << plugin->title();
      Core::registerPlugin(plugin);
  }
  else {
      qDebug() << "Plugin not loaded:" << pluginLoader->errorString();
  }
#endif

  qDebug() << "Connect edit forms with handler slot";

  QStringList formBeans = Core::instance()->namesByClass<AbstractDatabaseEditForm>();
  foreach(QString beanName, formBeans) {
      qDebug() << "Form:" << beanName;
      AbstractDatabaseEditForm* editForm = Core::instance()->dependency<AbstractDatabaseEditForm>(beanName);
      connect(editForm, &AbstractDatabaseEditForm::accepted, this, &MainWindow::saveObjectChanges);
  }

  //
  DataStore* ds = DataStore::instance(this);
  QStructureItemModel* structureModel = ds->structureModel();

  QStringList modules = Core::instance()->supportedDrivers();
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
  _exportDataAction = _itemContextMenu->addAction("Export data", this, SLOT(exportCurrentDatabaseObjectData()));

  _folderContextMenu = new QMenu(ui->tvDatabaseStructure);
  _folderContextMenu->addAction("Create object", this, SLOT(showCreateItemEditor()));
  _reloadAction = _folderContextMenu->addAction("Refresh", this, SLOT(reloadItemChildren()));


  //Создаем окно редактирования соединений с БД
  _connectionEditDialog = new ConnectionEditDialog(this);
  connect(_connectionEditDialog, SIGNAL(accepted()),
          this, SLOT(saveDatabaseChanges()));

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
    DBDatabaseItem* dbItem = static_cast<DBDatabaseItem*>(objectItem);
    //Database connection (loading database items)
    if (dbItem->children().isEmpty()){
      if (!dbItem->createDbConnection())
        break;
      IocPlugin* dbms = Core::plugin(dbItem->driverName(), FeatureType::DbmsObjects);
      foreach (DBObjectItem::ItemType type, dbms->supportedTypes()) {
        FolderTreeItem* folder = Core::instance()->dependencyForDriver<FolderTreeItem>(dbItem->driverName());
        folder->setParent(dbItem);
        folder->setParentUrl(dbItem->objectUrl());
        folder->setChildrenType(type);
        folder->reloadChildren();
      }
      ui->tvDatabaseStructure->reset();
      ui->tvDatabaseStructure->expand(index);
    }
    //Database disconnection (clear all database items)
    else {
      removeTabsByItemUrl(dbItem->objectUrl().toString());
      DataStore::structureModel()->deleteChildren(index);
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
    DBSelectableItem* tableItem = static_cast<DBSelectableItem*>(objectItem);
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
  DBObjectItem* curItem = static_cast<DBObjectItem*>(DataStore::structureModel()->itemByIndex(index));
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
  qDebug() << "Removing tabs by url" << url;
  int tabCount = ui->tabWidget->count();
  qDebug() << "Tabs total:" << tabCount;
  for (int i=tabCount-1; i>=0; i--){
    qDebug() << "Check tab:" << ui->tabWidget->widget(i)->objectName();
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
    DBObjectItem::ItemType type = static_cast<DBObjectItem::ItemType>(itemByIndex(index)->type());

    _exportDataAction->setEnabled(type == DBObjectItem::Table);

    switch (type) {
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
  qDebug() << "Request edit form";
  DBObjectItem* currentItem = itemByIndex(ui->tvDatabaseStructure->currentIndex());
  QVariantHash p;
  p.insert(F_TYPE, currentItem->type());
  AbstractDatabaseEditForm* editForm = Core::instance()->dependency<AbstractDatabaseEditForm>(p);
  if (!editForm) {
    QMessageBox::warning(this, TITLE_WARNING, "Edit form isn't supported yet");
    return;
  }
  currentItem->refresh();
  editForm->setUserAction(AbstractDatabaseEditForm::Edit);
  editForm->setObjItem(currentItem);
  editForm->objectToForm();
  editForm->show();
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
  QGuiApplication::clipboard()->setText(curObj->toDDL());
}

void MainWindow::exportCurrentDatabaseObjectData()
{
  //TODO: Test implementation
  qDebug() << "DML export";
  QModelIndex curIdx = ui->tvDatabaseStructure->currentIndex();
  DBObjectItem* curObj = itemByIndex(curIdx);
  curObj->refresh();
  QGuiApplication::clipboard()->setText(curObj->toDML());
}

void MainWindow::reloadItemChildren()
{
  QModelIndex curIdx = ui->tvDatabaseStructure->currentIndex();
  DataStore::structureModel()->deleteChildren(curIdx);
  FolderTreeItem* folderItem = static_cast<FolderTreeItem*>(itemByIndex(curIdx));

  qDebug() << "Folder" << folderItem->caption() << "refresh request";

  folderItem->reloadChildren();

  emit DataStore::structureModel()->dataChanged(curIdx, curIdx);
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
  FolderTreeItem* folderItem = static_cast<FolderTreeItem*>(currentItem);
  QString driverName = folderItem->driverName();
  AbstractDatabaseEditForm* editForm = Core::instance()->objectForm(driverName, folderItem->childrenType());
  QVariantHash pObj;
  pObj.insert(F_TYPE, folderItem->childrenType());
  pObj.insert(F_DRIVER_NAME, driverName);
  DBObjectItem* newItem = Core::instance()->dependency<DBObjectItem>(pObj);
  newItem->setParentUrl(folderItem->objectUrl());
  editForm->setObjItem(newItem);
  editForm->setUserAction(AbstractDatabaseEditForm::Create);
  editForm->objectToForm();
  qDebug() << "Before show";
  editForm->show();
  qDebug() << "After show";
}

void MainWindow::saveDatabaseChanges()
{
  AbstractDatabaseEditForm* editForm = static_cast<AbstractDatabaseEditForm*>(sender());
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

void MainWindow::saveObjectChanges()
{
    AbstractDatabaseEditForm* editForm = static_cast<AbstractDatabaseEditForm*>(sender());
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
  return static_cast<DBObjectItem*>(DataStore::structureModel()->itemByIndex(index));
}

DBObjectItem *MainWindow::itemByName(QString name)
{
  return static_cast<DBObjectItem*>(DataStore::structureModel()->itemByName(name));
}

void MainWindow::refreshConnectionList()
{
  for(int idx=0; idx<ui->tabWidget->count(); idx++) {
    QueryEditorWindow* editor = static_cast<QueryEditorWindow*>(ui->tabWidget->widget(idx));
    if (editor)
      editor->refreshConnectionList();
  }
}

void MainWindow::refreshQueryEditorAssistance()
{
  for(int idx=0; idx<ui->tabWidget->count(); idx++) {
    QueryEditorWindow* editor = static_cast<QueryEditorWindow*>(ui->tabWidget->widget(idx));
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
    DBSelectableItem* tableItem = static_cast<DBSelectableItem*>(dbItem);
    openTableEditor(tableItem);
    break;
  }
}

void MainWindow::openTableEditor(DBSelectableItem *tableItem)
{
  QString itemUrl = tableItem->objectUrl().toString();
  QWidget* tableWidget = ui->tabWidget->findChild<QWidget*>(itemUrl);
  if (!tableWidget){
    tableWidget = new TableBrowserWindow(this, tableItem);
    ui->tabWidget->addTab(tableWidget, tableItem->caption());
  }
  ui->tabWidget->setCurrentWidget(tableWidget);
  //  QSqlQueryHelper::tableRowInfo(tableItem->caption(), tableItem->connectionName());
}

void MainWindow::localEvent(LocalEvent *event)
{
  qDebug() << "Local event received from" << event->url();
  if (event->type() == ShowObjectEvent) {
    DBObjectItem* item = itemByName(event->url());
    if (item)
      showItemInfoWidget(item);
  }
  else if (event->type() == InfoMessageEvent) {
    QString message = event->param(PARAM_MESSAGE).toString();
    ui->statusBar->showMessage(message, MAIN_STATUS_BAR_TIMEOUT);
  }
}

void MainWindow::on_aOpenSqlEditor_triggered()
{
  //Создаем вкладку с редактором SQL-запросов
  QueryEditorWindow* newQueryEditor = new QueryEditorWindow(this);
  ui->tabWidget->addTab(newQueryEditor, tr("Query"));
}

void MainWindow::on_aSettings_triggered()
{
  SettingsForm::instance()->show();
}

void MainWindow::on_aExportDatabase_triggered()
{
  qDebug() << "Export database form";
  DatabaseExportForm::instance()->show();
}
