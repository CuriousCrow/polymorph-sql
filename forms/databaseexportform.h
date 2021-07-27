#ifndef DATABASEEXPORTFORM_H
#define DATABASEEXPORTFORM_H

#include <QDialog>
#include "core/datastore.h"
#include "core/dependencycontainer.h"

namespace Ui {
class DatabaseExportForm;
}

class DatabaseExportForm : public QDialog
{
  Q_OBJECT

public:
  Q_INVOKABLE DatabaseExportForm(QWidget *parent = nullptr);
  ~DatabaseExportForm();

  Q_INVOKABLE void inject_ds(DataStore* ds);

  static DatabaseExportForm* instance();
private slots:
  void on_btnClose_clicked();

  void on_btnStart_clicked();

private:
  Ui::DatabaseExportForm *ui;
  static DatabaseExportForm* _singleton;
};

#endif // DATABASEEXPORTFORM_H
