#include "queryhistoryform.h"
#include "ui_queryhistoryform.h"

#include "core/datastore.h"

QueryHistoryForm::QueryHistoryForm(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QueryHistoryForm)
{
  ui->setupUi(this);
}

QueryHistoryForm::~QueryHistoryForm()
{
  delete ui;
}

QString QueryHistoryForm::selectedQuery() const
{
  return _selectedQuery;
}

void QueryHistoryForm::loadHistory(int dbId)
{
  int row = ui->cmbProjects->findData(dbId);
  if (row != ui->cmbProjects->currentIndex())
    ui->cmbProjects->setCurrentIndex(row);
  else
      on_cmbProjects_currentIndexChanged(row);
}

void QueryHistoryForm::inject_ds(DataStore *ds)
{
  _ds = ds;
  ui->cmbProjects->setModel(_ds->structureModel());
}

void QueryHistoryForm::on_lvHistory_doubleClicked(const QModelIndex &index)
{
  _selectedQuery = index.data().toString();
  accept();
}

void QueryHistoryForm::on_cmbProjects_currentIndexChanged(int index)
{
  Q_UNUSED(index)
  _selectedQuery.clear();
  int dbId = ui->cmbProjects->currentData().toInt();
  ui->lvHistory->setModel(_ds->historyModel(dbId));
  ui->lvHistory->setModelColumn(2);
}

void QueryHistoryForm::on_btnClose_clicked()
{
  reject();
}

void QueryHistoryForm::on_btnClearQueryHistory_clicked()
{
  if (ui->cmbProjects->currentIndex() < 0)
      return;
  int dbId = ui->cmbProjects->currentData().toInt();
  _ds->clearQueryHistory(dbId);
  _ds->historyModel(dbId);
}
