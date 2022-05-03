#include "databaseexportform.h"
#include "ui_databaseexportform.h"

#include <QFileDialog>

#include "core/datastore.h"
#include "objects/appconst.h"
#include "utils/fileutils.h"
#include "models/lstructureitemmodel.h"

DatabaseExportForm* DatabaseExportForm::_singleton = nullptr;

DatabaseExportForm::DatabaseExportForm(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DatabaseExportForm)
{
  ui->setupUi(this);
}

DatabaseExportForm::~DatabaseExportForm()
{
    delete ui;
}

void DatabaseExportForm::inject_ds(DataStore *ds)
{
  ui->cmbDatabase->setModel(ds->structureModel());
}

DatabaseExportForm *DatabaseExportForm::instance()
{
  if (!_singleton) {
    _singleton = new DatabaseExportForm();
  }
  return _singleton;
}

void DatabaseExportForm::on_btnClose_clicked()
{
  reject();
}

void DatabaseExportForm::on_btnStart_clicked()
{
  //Select output file dialog
  QString filePath = QFileDialog::getSaveFileName(this, tr("Save"));
  if (filePath.isEmpty())
    return;

  int row = ui->cmbDatabase->currentIndex();
  LStructureItemModel* model = static_cast<LStructureItemModel*>(ui->cmbDatabase->model());
  DBDatabaseItem* dbItem = static_cast<DBDatabaseItem*>(model->itemByIndex(model->index(row, 0)));
  if (!dbItem->hasChildren()) {
    qDebug() << "Database is not connected";
    reject();
  }
  QStringList backupScript;
  backupScript.append(COMMENT_PREFIX "Backup" SQL_DELIMITER);

  //DDL
  DBObjectItem* folder = dbItem->folderByType(DBObjectItem::Table);
  if (folder) {
    backupScript.append(COMMENT_PREFIX + folder->caption());
    foreach(QObject* tableObj, folder->children()) {
      DBTableItem* tableItem = static_cast<DBTableItem*>(tableObj);
      backupScript.append(COMMENT_PREFIX + tableItem->caption());
      tableItem->reloadColumnsModel();
      backupScript.append(tableItem->toDDL());
    }
    backupScript.append("");
  }
  //VIEWS
  folder = dbItem->folderByType(DBObjectItem::View);
  if (folder) {
      backupScript.append("");
      backupScript.append(COMMENT_PREFIX + folder->caption());
      foreach(QObject* viewObj, folder->children()) {
        DBViewItem* viewItem = static_cast<DBViewItem*>(viewObj);
        backupScript.append(COMMENT_PREFIX + viewItem->caption());
        viewItem->refresh();
        backupScript.append(viewItem->toDDL());
      }
  }
  //SEQUENCES
  folder = dbItem->folderByType(DBObjectItem::Sequence);
  if (folder) {
      backupScript.append("");
      backupScript.append(COMMENT_PREFIX + folder->caption());
      foreach(QObject* sequenceObj, folder->children()) {
        DBSequenceItem* sequenceItem = static_cast<DBSequenceItem*>(sequenceObj);
        backupScript.append(COMMENT_PREFIX + sequenceItem->caption());
        sequenceItem->refresh();
        backupScript.append(sequenceItem->toDDL());
      }
  }
  //PROCEDURES
  folder = dbItem->folderByType(DBObjectItem::Procedure);
  if (folder) {
      backupScript.append("");
      backupScript.append(COMMENT_PREFIX + folder->caption());
      foreach(QObject* procedureObj, folder->children()) {
        DBProcedureItem* procedureItem = static_cast<DBProcedureItem*>(procedureObj);
        backupScript.append(COMMENT_PREFIX + procedureItem->caption());
        procedureItem->refresh();
        backupScript.append(procedureItem->toDDL());
      }
  }

  //TRIGGERS
  folder = dbItem->folderByType(DBObjectItem::Trigger);
  if (folder) {
      backupScript.append("");
      backupScript.append(COMMENT_PREFIX + folder->caption());
      foreach(QObject* triggerObj, folder->children()) {
        DBTriggerItem* triggerItem = static_cast<DBTriggerItem*>(triggerObj);
        backupScript.append(COMMENT_PREFIX + triggerItem->caption());
        triggerItem->refresh();
        backupScript.append(triggerItem->toDDL());
      }
  }

  //INDEXES
//  folder = dbItem->folderByType(DBObjectItem::Sequence);
//  if (folder) {
//      backupScript.append("");
//      backupScript.append(COMMENT_PREFIX + folder->caption());
//      foreach(QObject* sequenceObj, folder->children()) {
//        DBSequenceItem* sequenceItem = static_cast<DBSequenceItem*>(sequenceObj);
//        backupScript.append(COMMENT_PREFIX + sequenceItem->caption());
//        sequenceItem->refresh();
//        backupScript.append(sequenceItem->toDDL());
//      }
//  }

  //DML
  folder = dbItem->folderByType(DBObjectItem::Table);
  if (folder) {
    backupScript.append("");
    backupScript.append(COMMENT_PREFIX + folder->caption());
    foreach(QObject* tableObj, folder->children()) {
      DBTableItem* tableItem = static_cast<DBTableItem*>(tableObj);
      backupScript.append(COMMENT_PREFIX + tableItem->caption());
      backupScript.append(tableItem->toDML());
    }
    backupScript.append("");
  }
  FileUtils::stringToFile(backupScript.join(FILE_DELIMITER), filePath);
  accept();
}
