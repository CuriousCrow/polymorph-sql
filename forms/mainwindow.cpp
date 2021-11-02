#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlField>
#include <QMessageBox>
#include <QClipboard>
#include "sdk/objects/appurl.h"
#include "sdk/forms/tablebrowserwindow.h"
#include "sdk/objects/dbdatabaseitem.h"
#include "sdk/objects/dbobjectitem.h"
#include "sdk/objects/foldertreeitem.h"
#include "sdk/core/appsettings.h"
#include "sdk/core/basecontextaction.h"
#include "sdk/objects/appconst.h"
#include "sdk/objects/sdkplugin.h"
#include "sdk/utils/fileutils.h"
#include "testmodule.h"

#include "sdk/forms/queryeditorwindow.h"

#ifdef SINGLEAPP
#include "plugins/POSTGRES/postgresplugin.h"
#include "plugins/SQLITE/sqliteplugin.h"
#include "plugins/FIREBIRD/firebirdplugin.h"
#include "plugins/MYSQL/mysqlplugin.h"
#else
#include <QPluginLoader>
#endif


MainWindow::MainWindow(QWidget *parent) :
  NotifiableWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  //Loading DBMS plugins
  _core = Core::instance(this);

  //DataStore singleton
  _ds = new DataStore(this);
  _ds->setTabWidget(ui->tabWidget);

  _context = new BaseUserContext(this);
  _kb = new LKnowledgeBase(this);

  _core->registerSingletonObject(new DependencyMeta(B_DATA_STORE, CLASSMETA(DataStore)), _ds);
  _core->registerSingletonObject(new DependencyMeta(B_CONTEXT, CLASSMETA(BaseUserContext)), _context);
  _core->registerSingletonObject(new DependencyMeta(B_KNOWLEDGE_BASE, CLASSMETA(LKnowledgeBase)), _kb);

  LStructureItemModel* structureModel = _ds->structureModel();

  Core::registerPlugin(new SdkPlugin());

#ifdef SINGLEAPP
  qDebug() << "Single application mode";
  Core::registerPlugin(new PostgresPlugin());
  Core::registerPlugin(new SqlitePlugin());
  Core::registerPlugin(new FirebirdPlugin());
  Core::registerPlugin(new MysqlPlugin());
#else
  QStringList pluginFiles = FileUtils::filesOfDir(QApplication::applicationDirPath() + "/plugins");
  QPluginLoader* pluginLoader = new QPluginLoader(this);
  foreach(QString filename, pluginFiles) {
      qDebug() << "Found plugin file:" << filename;
      pluginLoader->setFileName("plugins/" + filename);
      IocPlugin* plugin = dynamic_cast<IocPlugin*>(pluginLoader->instance());
      if (plugin) {
          qDebug() << "Plugin is successfully loaded:" << plugin->title();
          Core::registerPlugin(plugin);
      }
      else {
          qDebug() << "Plugin not loaded:" << pluginLoader->errorString();
      }
  }
#endif
  _ds->initRegisteredDatabases();

  qDebug() << "Connect edit forms with handler slot";

  QStringList formBeans = Core::instance()->namesByClass<AbstractDatabaseEditForm>();
  foreach(QString beanName, formBeans) {
      qDebug() << "Form:" << beanName;
      AbstractDatabaseEditForm* editForm = Core::instance()->dependency<AbstractDatabaseEditForm>(beanName);
      connect(editForm, &AbstractDatabaseEditForm::accepted, this, &MainWindow::saveObjectChanges);
  }

  QStringList modules = Core::instance()->supportedDrivers();
  qDebug() << "Drivers supported:" << modules;
  _kb->loadModels(modules);

  //Showing first column only
  //TODO: create utility methods for hiding columns
  ui->tvDatabaseStructure->setModel(structureModel);
  for (int i=1; i<structureModel->columnCount(QModelIndex()); i++){
    ui->tvDatabaseStructure->hideColumn(i);
  }

  _itemContextMenu = new QMenu(ui->tvDatabaseStructure);

  //Создаем окно редактирования соединений с БД
  _connectionEditDialog = new ConnectionEditDialog(this);
  connect(_connectionEditDialog, SIGNAL(accepted()),
          this, SLOT(saveDatabaseChanges()));

  //Удаление вкладки с таблицей
  connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)),
          this, SLOT(removeTabByIndex(int)));

  connect(ui->tvDatabaseStructure->selectionModel(), &QItemSelectionModel::currentChanged,
          this, &MainWindow::onCurrentItemChanged);

  //Action processing
  QStringList beanNames = _core->namesByClass(CLASS(BaseContextAction));
  qDebug() << "Registered actions:" << beanNames;
  foreach(QString name, beanNames) {
    BaseContextAction* action = _core->dependency<BaseContextAction>(name);
    //Main menu
    if (action->inherits("MainMenuItem")) {
        QMenu* parentMenu = nullptr;
        QStringList pathList = (dynamic_cast<MainMenuItem*>(action))->menuPath();
        foreach(QString section, pathList){
            if (parentMenu) {
                parentMenu = parentMenu->addMenu(section);
            }
            else {
                parentMenu = ui->menuBar->addMenu(section);
            }
        }
        if (parentMenu) {
          parentMenu->addAction(action);
        }
        else {
          ui->menuBar->addAction(action);
        }
    }
//    Items context menu
    if (action->inherits("BaseItemPopupAction")) {
        _itemContextMenu->addAction(action);
    }
  }
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
        //setChildrenType should be before setParentUrl to generate a correct objectUrl
        folder->setChildrenType(type);
        folder->setParentUrl(dbItem->objectUrl());
        folder->reloadChildren();
      }
      ui->tvDatabaseStructure->reset();
      ui->tvDatabaseStructure->expand(index);
    }
    //Database disconnection (clear all database items)
    else {
      removeTabsByItemUrl(dbItem->objectUrl().toString());
      _ds->structureModel()->deleteChildren(index);
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
      _ds->structureModel()->removeRow(ui->tvDatabaseStructure->currentIndex().row(), QModelIndex());
    }
    else {
      qWarning() << "Remove database error:" << res.description();
    }
  }
}

void MainWindow::on_tvDatabaseStructure_pressed(const QModelIndex &index)
{
  if (!index.isValid())
      return;
  //Show context menu by right mouse click
  if (QApplication::mouseButtons().testFlag(Qt::RightButton)){
    _itemContextMenu->popup(QCursor::pos());
  }
}

void MainWindow::showEditorForCurrentItem()
{
  qDebug() << "Request edit form";
  DBObjectItem* currentItem = itemByIndex(ui->tvDatabaseStructure->currentIndex());
  AbstractDatabaseEditForm* editForm =
          Core::instance()->objectForm(currentItem->driverName(),(DBObjectItem::ItemType)currentItem->type());
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
      _ds->structureModel()->removeRow(ui->tvDatabaseStructure->currentIndex().row(),
                                 ui->tvDatabaseStructure->currentIndex().parent());
      LocalEventNotifier::postLocalEvent(DbSchemaChangeEvent, "");
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

void MainWindow::saveDatabaseChanges()
{
  AbstractDatabaseEditForm* editForm = static_cast<AbstractDatabaseEditForm*>(sender());
  AbstractDatabaseEditForm::UserAction action = editForm->userAction();
  if (action == AbstractDatabaseEditForm::Create) {
    DBObjectItem* newItem = editForm->objItem();
    QString driver = newItem->fieldValue(F_DRIVER_NAME).toString();
    QVariantHash p;
    p.insert(F_DRIVER_NAME, driver);
    //Creating Database item of selected driver
    DBDatabaseItem* newDatabaseItem = Core::instance()->dependency<DBDatabaseItem>(p);
    newItem->copyFieldsTo(newDatabaseItem);
    delete newItem;

    ActionResult insertResult = newDatabaseItem->insertMe();
    if (!insertResult.isSuccess()) {
        delete newDatabaseItem;
        qWarning() << "Oups! Cant insert new database connection";
        return;
    }
    newDatabaseItem->submit();
    _ds->structureModel()->appendItem(newDatabaseItem);
    LocalEventNotifier::postLocalEvent(DbSchemaChangeEvent, "");
  }
  else if (action == AbstractDatabaseEditForm::Edit) {
    //Nothing needs to be done
  }
  else {
    qWarning() << "Connection delete action is not possible from edit form";
  }
}

void MainWindow::saveObjectChanges()
{
    qDebug() << "saveObjectChanges() slot called by Dialog accept";
    AbstractDatabaseEditForm* editForm = static_cast<AbstractDatabaseEditForm*>(sender());
    AbstractDatabaseEditForm::UserAction action = editForm->userAction();
    if (action == AbstractDatabaseEditForm::Create) {
      DBObjectItem* folderItem = itemByIndex(ui->tvDatabaseStructure->currentIndex());
      DBObjectItem* newItem = editForm->objItem();
      qDebug() << "appendItem():" << folderItem->objectName();
      _ds->structureModel()->appendItem(newItem, folderItem);
    }
    else if (action == AbstractDatabaseEditForm::Edit) {
      //Nothing yet
    }
    LocalEventNotifier::postLocalEvent(DbSchemaChangeEvent, "");
}

DBObjectItem *MainWindow::itemByIndex(QModelIndex index)
{
  return static_cast<DBObjectItem*>(_ds->structureModel()->itemByIndex(index));
}

DBObjectItem *MainWindow::itemByName(QString name)
{
  return static_cast<DBObjectItem*>(_ds->structureModel()->itemByName(name));
}

void MainWindow::refreshConnectionList()
{
  for(int idx=0; idx<ui->tabWidget->count(); idx++) {
    QueryEditorWindow* editor = dynamic_cast<QueryEditorWindow*>(ui->tabWidget->widget(idx));
    if (editor)
      editor->refreshConnectionList();
  }
}

void MainWindow::refreshQueryEditorAssistance(DBObjectItem* item)
{  
  for(int idx=0; idx<ui->tabWidget->count(); idx++) {
    QueryEditorWindow* editor = dynamic_cast<QueryEditorWindow*>(ui->tabWidget->widget(idx));
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
  else if (event->type() == ItemDeleteEvent) {
    qDebug() << "Removing item from structure model";
    removeTabsByItemUrl(event->url());
    _ds->structureModel()->removeRow(ui->tvDatabaseStructure->currentIndex().row(),
                                     ui->tvDatabaseStructure->currentIndex().parent());
    refreshQueryEditorAssistance(nullptr);
  }
  else if (event->type() == DbSchemaChangeEvent) {
    //TODO: Update only query editors
    refreshQueryEditorAssistance(nullptr);
  }
}

void MainWindow::onCurrentItemChanged(const QModelIndex &index)
{
    DBObjectItem* curItem = _ds->structureModel()->itemByIdx(index);
    qDebug() << "Current item:" << curItem;
    _context->setCurrentItem(curItem);
    ui->aEditDatabase->setEnabled(curItem->type() == DBObjectItem::Database);
    ui->aRemoveDatabase->setEnabled(curItem->type() == DBObjectItem::Database);
}
