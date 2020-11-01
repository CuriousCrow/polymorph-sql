#ifndef DATABASEEXPORTFORM_H
#define DATABASEEXPORTFORM_H

#include <QDialog>

namespace Ui {
class DatabaseExportForm;
}

class DatabaseExportForm : public QDialog
{
  Q_OBJECT

public:
  explicit DatabaseExportForm(QWidget *parent = nullptr);
  ~DatabaseExportForm();

private:
  Ui::DatabaseExportForm *ui;
};

#endif // DATABASEEXPORTFORM_H
