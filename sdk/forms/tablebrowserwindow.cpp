#include "tablebrowserwindow.h"
#include "ui_tablebrowserwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QUuid>
#include "core/datastore.h"
#include "core/extensionpoints.h"
#include "extensions/unisqltablefilteraction.h"
#include "objects/appconst.h"
#include "objects/appurl.h"
#include "objects/appconst.h"
#include "utils/fileutils.h"
#include "utils/eventinterceptors.h"
#include "widgets/tablebrowserdelegate.h"

TableBrowserWindow::TableBrowserWindow(DBSelectableItem* tableItem) :
    QMainWindow(),
    ui(new Ui::TableBrowserWindow),
    _tableItem(tableItem)
{
    qDebug() << "Connections:" << QSqlDatabase::connectionNames();
    ui->setupUi(this);

    _extensionPoints.insert(ExtensionPoint(EP_TABLEBROWSER_FILTER_POPUP, CLASS(UniSqlTableFilterAction), "Popup actions in filter list view", false));

    _mnuContext = new QMenu(this);
    _mnuContext->addAction(ui->aSetNull);
    _mnuContext->addAction(ui->aGenerateUuid);
    _mnuContext->addAction(ui->aLoadFromFile);
    _mnuContext->addSeparator();
    _mnuContext->addAction(ui->aEqualFilter);
    _mnuContext->addAction(ui->aNotEqualFilter);
    _mnuContext->addAction(ui->aGreaterThanFilter);
    _mnuContext->addAction(ui->aLessThanFilter);
    _mnuContext->addAction(ui->aFilterIsNull);
    _mnuContext->addAction(ui->aFilterIsNotNull);

    _mnuFilterList = new QMenu(this);

    _mnuColumns = new QMenu(this);

    _tableItem->refresh();

    ui->tableView->setEditTriggers(_tableItem->type() == DBObjectItem::Table
                                   ? (QAbstractItemView::SelectedClicked | QAbstractItemView::DoubleClicked)
                                   : QAbstractItemView::NoEditTriggers);

    AppUrl url = _tableItem->objectUrl();
    setObjectName(url.toString());
    _connectionName = url.connection();

    _tableName = _tableItem->caption();
    _sourceModel = new UniSqlTableModel(this, _connectionName);
    connect(_sourceModel, &UniSqlTableModel::error, this, &TableBrowserWindow::onError);


    loadColumnsState();

    refreshTable();

    _proxyModel = new QSortFilterProxyModel(this);
    _proxyModel->setSourceModel(_sourceModel);
    ui->tableView->setModel(_proxyModel);
    ui->tableView->setItemDelegate(new TableBrowserDelegate(_tableItem, this));
    ui->tableView->horizontalHeader()->setSortIndicatorShown(true);

    qDebug() << "TableBrowserWindow" << objectName() << "created";

    ui->tableView->horizontalHeader()->setSectionsMovable(true);

    ui->lvFilters->setModel(_sourceModel->filter());

    connect(ui->tableView->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &TableBrowserWindow::onCurrentItemChanged);

    SimpleEventInterceptor* columnMenuInterceptor = new SimpleEventInterceptor(this);
    columnMenuInterceptor->addEventType(QEvent::ContextMenu);
    ui->tableView->horizontalHeader()->installEventFilter(columnMenuInterceptor);
    connect(columnMenuInterceptor, &SimpleEventInterceptor::onEvent,
            this, &TableBrowserWindow::onHeaderPressed);
}

TableBrowserWindow::~TableBrowserWindow()
{
    if (_stateSavingEnabled) {
        int dbId = _ds->databaseIdFromItem(_tableItem);
        _ds->saveTableState(dbId, _tableName, ui->tableView->horizontalHeader()->saveState());
    }
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
    refreshTable();
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

void TableBrowserWindow::on_aGenerateUuid_triggered()
{
    _sourceModel->setData(ui->tableView->currentIndex(), QUuid::createUuid());
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
    QByteArray data = FileUtils::loadFile(filepath);
    _proxyModel->setData(ui->tableView->currentIndex(), data);
}

void TableBrowserWindow::onColumnVisibilityActionToggled(bool checked)
{
    QAction* action = static_cast<QAction*>(sender());
    int index = _sourceModel->fieldIndex(action->text());
    checked ? ui->tableView->showColumn(index) : ui->tableView->hideColumn(index);
}

void TableBrowserWindow::onHeaderPressed()
{
    _mnuColumns->popup(QCursor::pos());
}

void TableBrowserWindow::refreshColumnsMenu()
{
    _mnuColumns->clear();
    qDebug() << "Refresh columns menu";
    _mnuColumns->addSection(tr("Columns"));
    for(int col=0; col<_sourceModel->columnCount(); col++) {
        QString title = _sourceModel->headerData(col, Qt::Horizontal).toString();
        QAction* colAct = _mnuColumns->addAction(title);
        colAct->setCheckable(true);
        int index = _sourceModel->fieldIndex(title);
        colAct->setChecked(!ui->tableView->isColumnHidden(index));
        connect(colAct, &QAction::toggled, this, &TableBrowserWindow::onColumnVisibilityActionToggled);
    }
}

void TableBrowserWindow::refreshTable()
{
    //in case the table structure has changed
    _sourceModel->setTable(_tableName);
    //get actual table data
    _sourceModel->select();

    refreshColumnsMenu();
}

void TableBrowserWindow::loadColumnsState()
{
    int dbId = _ds->databaseIdFromItem(_tableItem);
    QByteArray tableStateData = _ds->loadTableState(dbId, _tableName);
    if (!tableStateData.isEmpty())
        ui->tableView->horizontalHeader()->restoreState(tableStateData);
}

void TableBrowserWindow::resetStateLater()
{
    int dbId = _ds->databaseIdFromItem(_tableItem);
    _ds->resetTableState(dbId, _tableName);
    _stateSavingEnabled = false;
}

void TableBrowserWindow::on_aResetState_triggered()
{
    resetStateLater();
}

void TableBrowserWindow::injectExtension(ExtensionPoint ep, QObject *e)
{
  Q_UNUSED(ep)
  qDebug() << "Inject TableBrowserWindow extension:" << e->objectName();

  if (e->inherits(CLASS(UniSqlTableFilterAction))) {
    UniSqlTableFilterAction* action = static_cast<UniSqlTableFilterAction*>(e);
    action->setView(ui->lvFilters);
    _mnuFilterList->addAction(action);
  }
}
