#ifndef FIREBIRDTRIGGERFORM_H
#define FIREBIRDTRIGGERFORM_H

#include "forms/abstractdatabaseitemform.h"
#include "core/datastore.h"

namespace Ui {
class FirebirdTriggerForm;
}

class FirebirdTriggerForm : public AbstractDatabaseEditForm
{
  Q_OBJECT

public:
  Q_INVOKABLE FirebirdTriggerForm();
  ~FirebirdTriggerForm();

  INJECT(DataStore*, ds)

private:
  Ui::FirebirdTriggerForm *ui;

  // AbstractDatabaseEditForm interface
public:
  virtual void objectToForm() override;
  virtual void formToObject() override;

private slots:
  void on_btnApply_clicked();
  void on_btnCancel_clicked();

  void onUserActionChanged();
};

#endif // FIREBIRDTRIGGERFORM_H
