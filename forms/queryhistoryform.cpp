#include "queryhistoryform.h"
#include "ui_queryhistoryform.h"

#include "core/datastore.h"

QueryHistoryForm* QueryHistoryForm::_singleton = nullptr;

QueryHistoryForm::QueryHistoryForm(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QueryHistoryForm)
{
  ui->setupUi(this);
  ui->cmbProjects->setModel(_ds->structureModel());
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

QueryHistoryForm *QueryHistoryForm::instance(int dbId)
{
  if (!_singleton) {
    _singleton = new QueryHistoryForm();
  }
  _singleton->loadHistory(dbId);
  return _singleton;
}

void QueryHistoryForm::on_lvHistory_doubleClicked(const QModelIndex &index)
{
  _selectedQuery = index.data().toString();
  accept();
}

void QueryHistoryForm::on_cmbProjects_currentIndexChanged(int index)
{
  _selectedQuery.clear();
  //TODO: Change to ui->cmbProjects->currentData().toInt()
  int dbId = ui->cmbProjects->model()->index(index, 0).data(Qt::UserRole).toInt();
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
