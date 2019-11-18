#ifndef PROCEDUREEDITFORM_H
#define PROCEDUREEDITFORM_H

#include <QDialog>
#include "abstractdatabaseitemform.h"

namespace Ui {
class ProcedureEditForm;
}

class ProcedureEditForm : public AbstractDatabaseEditForm
{
  Q_OBJECT

public:
  explicit ProcedureEditForm(QWidget *parent = nullptr);
  ~ProcedureEditForm();

private:
  Ui::ProcedureEditForm *ui;

  // AbstractDatabaseEditForm interface
public:
  void objectToForm();
  void formToObject();
private slots:
  void on_btnApply_clicked();
  void on_btnCancel_clicked();
};

#endif // PROCEDUREEDITFORM_H
