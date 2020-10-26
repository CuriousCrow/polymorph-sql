#ifndef QUERYHISTORYFORM_H
#define QUERYHISTORYFORM_H

#include <QDialog>

namespace Ui {
class QueryHistoryForm;
}

class QueryHistoryForm : public QDialog
{
  Q_OBJECT

public:
  explicit QueryHistoryForm(QWidget *parent = nullptr);
  ~QueryHistoryForm();
  QString selectedQuery() const;

  void loadHistory(int dbId);

  static QueryHistoryForm* instance(int dbId);
private slots:
  void on_lvHistory_doubleClicked(const QModelIndex &index);

  void on_cmbProjects_currentIndexChanged(int index);

  void on_btnClose_clicked();

private:
  QString _selectedQuery;
  Ui::QueryHistoryForm *ui;
  static QueryHistoryForm* _singleton;

};

#endif // QUERYHISTORYFORM_H
