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
  Q_INVOKABLE ProcedureEditForm();
  ~ProcedureEditForm();

private:
  Ui::ProcedureEditForm *ui;
  void reloadTypes();

  // AbstractDatabaseEditForm interface
public:
  void objectToForm();
  void formToObject();
private slots:
  void on_btnApply_clicked();
  void on_btnCancel_clicked();
  void onUserActionChanged();
};

#endif // PROCEDUREEDITFORM_H
