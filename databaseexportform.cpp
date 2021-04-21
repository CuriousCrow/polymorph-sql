#include "databaseexportform.h"
#include "ui_databaseexportform.h"

#include <QFileDialog>

#include "core/datastore.h"
#include "dbms/appconst.h"
#include "utils/qfileutils.h"
#include "qstructureitemmodel.h"

DatabaseExportForm* DatabaseExportForm::_singleton = nullptr;

DatabaseExportForm::DatabaseExportForm(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DatabaseExportForm)
{
  ui->setupUi(this);
  ui->cmbDatabase->setModel(DataStore::structureModel());
}

DatabaseExportForm::~DatabaseExportForm()
{
  delete ui;
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
  QStructureItemModel* model = qobject_cast<QStructureItemModel*>(ui->cmbDatabase->model());
  DBDatabaseItem* dbItem = qobject_cast<DBDatabaseItem*>(model->itemByIndex(model->index(row, 0)));
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
      DBTableItem* tableItem = qobject_cast<DBTableItem*>(tableObj);
      backupScript.append(COMMENT_PREFIX + tableItem->caption());
      tableItem->reloadColumnsModel();
      backupScript.append(tableItem->toDDL());
    }
    backupScript.append("");
  }

  //DML
  folder = dbItem->folderByType(DBObjectItem::Table);
  if (folder) {
    backupScript.append(COMMENT_PREFIX + folder->caption());
    foreach(QObject* tableObj, folder->children()) {
      DBTableItem* tableItem = qobject_cast<DBTableItem*>(tableObj);
      backupScript.append(COMMENT_PREFIX + tableItem->caption());
      backupScript.append(tableItem->toDML());
    }
    backupScript.append("");
  }
  QFileUtils::stringToFile(backupScript.join(FILE_DELIMITER), filePath);
  accept();
}
